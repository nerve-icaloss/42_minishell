/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/24 10:38:29 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"
#include "../../headers/redirection.h"

int	search_exec_path(t_execute *exec, t_myenv *env)
{
	char	*cmd_path;

	if (!exec)
		return (errno = ENODATA, 1);
	if (!exec->argv[0])
		return (0);
	if (find_builtin_f(exec))
		return (exec->exit = 1, 1);
	if (exec->builtin_f)
		return (exec->exit = 0, 0);
	if (exec->argv[0][0] != '/')
		cmd_path = search_cmd_path(exec->argv[0], env);
	else
		cmd_path = ft_strdup(exec->argv[0]);
	if (!cmd_path)
		return (cmd_notfound(exec->argv[0]), exec->exit = 127, 1);
	if (access(cmd_path, F_OK | X_OK) == SYS_FAIL)
		return (perror(cmd_path), exec->exit = 126, 1);
	free(exec->argv[0]);
	exec->argv[0] = cmd_path;
	return (0);
}

int	execute_cmd(t_node *cmd, t_myshell *shell)
{
	t_execute	exec;

	if (!cmd || !shell)
		return (errno = ENODATA, 1);
	ft_memset(&exec, 0, sizeof(exec));
	if (execute_cmd_init(&exec, cmd, &shell->env))
		return (exec.exit);
	if (apply_redirection(&exec, cmd))
		return (exec_clean(&exec), exec.exit);
	if (!exec.argv[0])
		return (reset_redirection(&exec, cmd), exec_clean(&exec), 0);
	if (search_exec_path(&exec, &shell->env))
		return (reset_redirection(&exec, cmd), exec_clean(&exec), exec.exit);
	if (exec.builtin_f)
		exec.exit = exec.builtin_f(exec.argv, &shell->env);
	else
	{
		cmd->pid = fork();
		if (cmd->pid == SYS_FAIL)
			return (reset_redirection(&exec, cmd), exec_clean(&exec), 1);
		if (cmd->pid == 0)
			child_cmd(&exec, shell);
		wait_cmd(&exec, cmd);
	}
	return (reset_redirection(&exec, cmd), exec_clean(&exec), cmd->exit);
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
		exec_reset(&exec);
		if (execute_pipex_init(&exec, pipex, cmd, &shell->env)
			|| apply_redirection(&exec, cmd) || (!exec.bracket_first_child
			&& search_exec_path(&exec, &shell->env)))
		{
			reset_redirection(&exec, cmd);
			cmd = cmd->next_sibling;
			continue ;
		}
		ft_fork(cmd);
		if (cmd->pid == 0)
			child_pipex_cmd(&exec, shell);
		reset_redirection(&exec, cmd);
		cmd = cmd->next_sibling;
	}
	return (wait_pipex(&exec, pipex), exec_clean(&exec), pipex->exit);
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
		exit = execute_pipex(root, shell);
	if (root->type == NODE_CMD)
		exit = execute_cmd(root, shell);
	if (!root->parent && (root->type == NODE_PIPE || root->type == NODE_CMD))
		return (node_tree_clean(root), exit);
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
