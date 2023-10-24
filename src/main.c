/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:57:45 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/20 14:43:56 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/parser.h"
#include "../headers/here_doc.h"
#include "../headers/executor.h"

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

	if (!cmdline || !shell)
		return (errno = ENODATA, (void) NULL);
	if (source_init(&src, cmdline))
		return ((void) NULL);
	shell->exit = parse_source(&shell->root, &src, &shell->env);
	source_clean(&src);
	if (shell->exit == 2)
		run_tree_doc(shell->root, &shell->env);
	else
		shell->exit = run_tree_doc(shell->root, &shell->env);
	if (shell->exit > 0)
		return (node_tree_clean(shell->root), (void) NULL);
	node_tree_print(shell->root); //
	write(1, "\n", 1); //
	shell->exit = execute_tree(shell->root, shell);
}

void	rpel(t_myshell *shell)
{
	char		*cmdline;
	if (!shell)
		return (errno = ENODATA, (void)NULL);
	while (1)
	{
		cmdline = readline("minishell-1.0$ ");
		if (!cmdline || cmdline[0] == '\0' || cmdline[0] == '\n')
		{
			free(cmdline);
			continue ;
		}
		if (entry_add(&shell->hist, cmdline) == -1)
			write(2, "error login history\n", 20);
		parse_and_execute(cmdline, shell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_myshell	shell;
	int			exit;

	printf("Welcome to %s\n", argv[0]);
	ft_memset(&shell, 0, sizeof(shell));
	load_history();
	if (!envp)
		return (write(2, "error envp unset\n", 16), 1);
	if (env_init(&shell.env, envp))
		return (write(2, "error env init\n", 15), 1);
	if (argc == 1)
	{
		rpel(&shell);
	}
	exit = shell.exit;
	return(register_history(&shell.hist), shell_clean(&shell), exit);
}
