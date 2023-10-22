/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:27:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/19 15:32:23 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"
#include "../../headers/redirection.h"

int	execute_cmd_init(t_execute *exec, t_node *cmd)
{
	if (!exec || !cmd)
		return (errno =ENODATA, 1);
	exec->exit = 1;
	exec->argv = NULL;
	exec->std_fd[IN] = -1;
	exec->std_fd[OUT] = -1;
	if (infile_redirection(cmd))
		return (1);
	if (outfile_redirection(cmd))
		return (1);
	exec->argv = build_argv(cmd);
	if (!exec->argv)
		return (1);
	exec->exit = 0;
	return (0);
}

int	execute_pipex_init(t_execute *exec, t_node *pipex, t_node *cmd)
{
	if (!exec || !pipex || !cmd)
		return (errno =ENODATA, 1);
	exec->exit = 1;
	exec->argv = NULL;
	if (cmd->next_sibling)
	{
		if (pipe(pipex->fd) == SYS_FAIL)
			return (perror("pipe"), 1);
		cmd->fd[OUT] = pipex->fd[OUT];
		cmd->next_sibling->fd[IN] = pipex->fd[IN];
		exec->toclose_child = pipex->fd[IN];
	}
	if (cmd->type == NODE_BRACKET)
	{
		exec->bracket_first_child = cmd->first_child;
		return (0);
	}
	if (execute_cmd_init(exec, cmd))
		return (1);
	else
		return (0);
}

void	wait_cmd(t_execute *exec, t_node *cmd)
{
	int	status;

	if (!exec || !cmd)
		return (errno = ENODATA, (void)NULL);
	if (waitpid(cmd->pid, &status, 0) == cmd->pid && WIFEXITED(status))
		cmd->exit = WEXITSTATUS(status);
	//else if (signal)
	else
		cmd->exit = exec->exit;
}

void	wait_pipex(t_execute *exec, t_node *pipex)
{
	int		status;
	t_node	*cmd;

	if (!exec || !pipex)
		return (errno = ENODATA, (void)NULL);
	cmd = pipex->first_child;
	while (cmd->next_sibling)
	{
		if (cmd->pid != -1)
			waitpid(cmd->pid, &status, 0);
		cmd = cmd->next_sibling;
	}
	if (waitpid(cmd->pid, &status, 0) == cmd->pid && WIFEXITED(status))
		pipex->exit = WEXITSTATUS(status);
	//else if (signal)
	else
		pipex->exit = exec->exit;
}
