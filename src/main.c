/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:57:45 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 12:45:46 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "history.h"
#include "scanner.h"
#include "parser.h"
#include "here_doc.h"
#include "executor.h"

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

void	parse_and_execute(t_myshell *shell, t_source *src)
{
	if (!shell || !src)
		return (errno = ENODATA, (void)NULL);
	shell->exit = parse_source(&shell->root, src, &shell->env);
	//clean source
	node_tree_print(shell->root); //
	write(1, "\n", 1);
	shell->exit = run_tree_doc(shell->root, &shell->env);
	if (shell->exit > 0)
		return (node_tree_clean(shell->root), (void)NULL);
	shell->exit = execute_tree(shell->root, shell);
	//if (shell->exit > 0)
	node_tree_clean(shell->root);
}

void	rpel(t_myshell *shell)
{
	char		*cmdline;
	t_source	src;

	if (!shell)
		return (errno = ENODATA, (void)NULL);
	if (tok_buf_init(&src) == -1)
		return ;
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
		src.buf = cmdline;
		src.curpos = INIT_SRC_POS;
		src.bufsize = ft_strlen(cmdline);
		parse_and_execute(shell, &src);
		free(cmdline);
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
