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
#include "executor_utils.h"
#include "redirection.h"
#include "path.h"
#include "builtin.h"
#include "child.h"

int	execute_cmd(t_node *cmd, t_myshell *shell)
{
	t_execute	exec;

	if (!cmd || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	if (execute_cmd_init(&exec, cmd))
		return (exec.exit);
	if (apply_redirection(&exec, cmd))
		return (exec.exit);
	if (search_path(&exec))
		return (exec.exit);
	if (is_builtin(exec.argv[0]))
		return (builtin_cmd(&exec, shell));
	else
	{
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			return (ft_arrclear(exec.argv), 1);
		if (cmd->pid == 0)
			child_cmd(&exec, shell);
	}
	reset_redirection(&exec, cmd);
	wait_cmd(&exec, cmd);
	return (ft_arrclear(exec.argv), cmd->exit);
}

int	execute_pipex(t_node *pipex, t_myshell *shell)
{
	t_node		*cmd;
	t_execute	exec;

	if (!pipex || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	cmd = pipex->first_child;
	while (cmd)
	{
		if (execute_pipex_init(&exec, pipex, cmd))
			continue ;
		if (apply_redirection(&exec, cmd))
			continue ;
		if (search_path(&exec))
			continue ;
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			cmd->exit = 1;
		if (cmd->pid == 0)
			child_pipex_cmd(&exec, shell);
		reset_redirection(&exec, cmd);
		ft_arrclear(exec.argv);
	}
	wait_pipex(&exec, pipex);
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
		return (execute_pipex(root, shell));
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
