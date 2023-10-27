/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:57:45 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/27 16:41:09 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/parser.h"
#include "../headers/here_doc.h"
#include "../headers/executor.h"
#include "../headers/signal_not_libc.h"

volatile int	g_signal;

void	node_tree_print(t_node *root)
{
	t_node	*child;
	t_node	*i;

	if(!root)
		return (errno = ENODATA, (void)NULL);
	if (root->type == NODE_BRACKET)
		write(1, "( ", 2);
	child = root->first_child;
	while (child)
	{
		i = child->next_sibling;
		node_tree_print(child);
		if (child->next_sibling)
		{
			if (root->type == NODE_AND)
				write(1, "&& ", 3);
			if (root->type == NODE_OR)
				write(1, "|| ", 3);
			if (root->type == NODE_PIPE)
				write(1, "| ", 2);
		}
		if (root->type == NODE_BRACKET)
			write(1, ") ", 2);
		child = i;
	}
	if(root->type == NODE_WORD && root->val)
	{
		if (root->rtype == READ)
			write(1, "< ", ft_strlen("< "));
		if (root->rtype == HEREDOC)
			write(1, "<< ", 4);
		if (root->rtype == TRUNC)
			write(1, "> ", 3);
		if (root->rtype == APPEND)
			write(1, ">> ", 4);
		write(1, root->val, ft_strlen(root->val));
		write(1, " ", 1);
	}
}

void	parse_and_execute(char *cmdline, t_myshell *shell)
{
	t_source	src;
	int			exit;

	if (!cmdline || !shell)
		return (errno = ENODATA, (void) NULL);
	if (source_init(&src, cmdline))
		return ((void) NULL);
	g_signal = 0;
	exit = parse_source(&shell->root, &src);
	source_clean(&src);
	if (exit == 2)
		run_tree_doc(shell->root, &shell->env);
	else
		exit = run_tree_doc(shell->root, &shell->env);
	if (exit > 0)
	{
		if (g_signal == 130)
			shell->exit = g_signal;
		else if (g_signal == -1)
			shell->exit = 0;
		else
			shell->exit = exit;
		return (node_tree_clean(shell->root), (void) NULL) ;
	}
	shell->exit = execute_tree(shell->root, shell);
}

void	rpel_mode(t_myshell *shell)
{
	char		*cmdline;

	if (!shell)
		return (errno = ENODATA, (void)NULL);
	while (1)
	{
		cmdline = ft_readline("minishell-1.0$ ", NULL, handler_rpel);
		if (!cmdline)
		{
			free(cmdline);
			if (isatty(STDIN_FILENO))
				shell->exit = 131;
			break ;
		}
		if (cmdline[0] == '\0' || cmdline[0] == '\n')
			continue ;
		if (entry_add(&shell->hist, cmdline) == -1)
			write(2, "error login history\n", 20);
		parse_and_execute(cmdline, shell);
		shell->root = NULL;
		if (g_signal == -1)
			break ;
	}
}

void	cmd_mode(t_myshell *shell, int argc, char *argv[])
{
	char		*cmdline;

	cmdline = ft_strnjoin(argc - 1, &argv[1], " ");
	if (!cmdline)
		return (shell->exit = 1, (void) NULL);
	parse_and_execute(cmdline, shell);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_myshell	shell;
	int			exit;

	sigint_assign(SIGQUIT, SIG_IGN);
	ft_memset(&shell, 0, sizeof(shell));
	g_signal = 0;
	load_history();
	if (!envp)
		return (write(2, "error envp unset\n", 16), 1);
	if (env_init(&shell.env, envp, &shell))
		return (write(2, "error env init\n", 15), 1);
	shell.start_dir = getcwd(NULL, 0);
	if (!shell.start_dir)
		return (write(2, "error start dir\n", 16), 1);
	if (argc == 1)
		rpel_mode(&shell);
	else
		cmd_mode(&shell, argc, argv);
	exit = shell.exit;
	return(register_history(&shell), shell_clean(&shell), exit);
}
