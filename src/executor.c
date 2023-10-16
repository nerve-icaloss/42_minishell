/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 11:49:45 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtin.h"
#include "redirection.h"
#include "child.h"
#include "path.h"

int	execute_cmd(t_node *cmd, t_myshell *shell)
{
	t_execute	exec;

	if (!cmd || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	if (execute_cmd_init(&exec, cmd))
		return (exec.exit);
	if (apply_redirection(&exec))
		return (exec.exit);
	if (search_command(&exec))
		return (exec.exit);
	if (is_builtin(exec.argv[0]))
		return (choose_builtin(&exec, shell));
	else
	{
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			break ;
		if (cmd->pid == 0)
			child_cmd(exec, shell);
	}
	reset_redirection(&exec);
	wait_cmd(cmd);
	return (ft_arrclear(exec.argv), cmd->exit);
}

int	execute_pipe(t_node *pipex, t_myshell *shell)
{
	t_node		*cmd;
	t_execute	exec;

	if (!pipex || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	cmd = pipex->first_child;
	while (cmd)
	{
		if (execute_pipe_init(&exec, cmd))
			continue ;
		if (apply_redirection(&exec))
			continue ;
		if (search_command(&exec))
			continue ;
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			continue ;
		if (cmd->pid == 0)
			child_pipe(exec, shell);
		reset_redirection(&exec);
	}
	wait_pipe(pipex);
	return (ft_arrclear(exec.argv), pipex->exit);
}

int	stop_execute(t_node *node, int exit)
{
	if (!node)
		return (errno = ENODATA, 1);
	if (node->type == NODE_AND && node->exit > 0)
		return (1);
	if (node->type == NODE_OR && node->exit == 0)
		return (1);
	return (0);
}

int	execute_tree(t_node *root, t_myshell *shell)
{
	t_node	*child;
	t_node	*i;
	int		exit;
	
	if (!root || !shell)
		return (errno = ENODATA, 1);
	if (root->type == NODE_PIPE)
		return (execute_pipe(root, shell));
	if (root->type == NODE_CMD)
		return (execute_cmd(root, shell));
	child = root->first_child;
	while(child)
	{
		i = child->next_sibling;
		exit = execute_tree(child, shell);
		node_tree_clean(child);
		if (stop_execute(root, exit))
		{
			node_sibling_clean(&child);
			break ;
		}
		child = i;
	}
	root->first_child = NULL;
	return (node_tree_clean(root), exit);
}
