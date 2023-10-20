/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/20 14:36:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "executor_utils.h"
#include "libft/libft.h"
#include "redirection.h"
#include "path.h"
#include "builtin.h"
#include "child.h"
#include "error.h"

int	search_exec_path(t_execute *exec, t_myenv *env)
{
	if (!exec)
		return (errno = ENODATA, 1);
	if (exec->cmd_path)
	{
		free(exec->cmd_path);
		exec->cmd_path = NULL;
	}
	if (find_builtin_f(exec))
		return (exec->exit = 1, 1);
	if (exec->builtin_f)
		return (exec->exit = 0, 0);
	if (!(exec->argv[0][0] == '/' || exec->argv[0][0] == '.'))
		exec->cmd_path = search_cmd_path(exec->argv[0], env);
	else
		exec->cmd_path = ft_strdup(exec->argv[0]);
	if (!exec->cmd_path)
		return (cmd_notfound(exec->argv[0]), exec->exit = 127, 1);
	if (access(exec->cmd_path, F_OK | X_OK) == SYS_FAIL)
		return (perror(exec->cmd_path), exec->exit = 126, 1);
	return (0);
}

int	execute_cmd(t_node *cmd, t_myshell *shell)
{
	t_execute	exec;

	if (!cmd || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	if (execute_cmd_init(&exec, cmd))
		return (exec.exit);
	if (apply_redirection(&exec, cmd))
		return (ft_arrclear(exec.argv), exec.exit);
	if (search_exec_path(&exec, &shell->env))
		return (ft_arrclear(exec.argv), exec.exit);
	if (exec.builtin_f)
		return (exec.builtin_f(exec.argv, &shell->env));
	else
	{
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			return (ft_arrclear(exec.argv), 1);
		if (cmd->pid == 0)
			child_cmd(&exec, shell);
	}
	reset_redirection(&exec, cmd);
	return (wait_cmd(&exec, cmd), ft_arrclear(exec.argv), cmd->exit);
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
		ft_arrclear(exec.argv);
		if (execute_pipex_init(&exec, pipex, cmd))
			continue ;
		if (apply_redirection(&exec, cmd))
			continue ;
		if (search_exec_path(&exec, &shell->env))
			continue ;
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			cmd->exit = 1;
		if (cmd->pid == 0)
			child_pipex_cmd(&exec, shell);
		reset_redirection(&exec, cmd);
		cmd = cmd->next_sibling;
	}
	return (wait_pipex(&exec, pipex), ft_arrclear(exec.argv), pipex->exit);
}

int	stop_execute(t_node *node, int exit)
{
	if (!node)
		return (errno = ENODATA, 1);
	if (node->type == NODE_AND && exit > 0)
		return (1);
	if (node->type == NODE_OR && exit == 0)
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
	while (child)
	{
		i = child->next_sibling;
		exit = execute_tree(child, shell);
		node_sibling_pop(child);
		if (stop_execute(root, exit))
			break ;
		child = i;
	}
	if (!root->parent)
		node_tree_clean(root);
	return (exit);
}
