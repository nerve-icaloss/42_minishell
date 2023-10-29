/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:27:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/29 11:31:47 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"
#include "../../headers/expander.h"
#include "../../headers/redirection.h"
#include "../../headers/signal_not_libc.h"

static int	build_argv(t_execute *exec, t_node *cmd, t_myenv *env)
{
	t_node	*child;
	t_node	*word;
	t_node	*i;

	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		word = word_expand(child->val, env);
		if (!word)
		{
			child = child->next_sibling;
			continue ;
		}
		if (add_to_argv(exec, word))
			return (node_sibling_clean(&word), 1);
		node_sibling_clean(&word);
		node_sibling_pop(child);
		child = i;
	}
	if (check_argv_bounds(exec))
		exec->argv[exec->argc] = NULL;
	return (0);
}

int	execute_cmd_init(t_execute *exec, t_node *cmd, t_myenv *env)
{
	if (!exec || !cmd)
		return (errno = ENODATA, 1);
	exec->std_fd[IN] = -1;
	exec->std_fd[OUT] = -1;
	exec->exit = 0;
	if (do_redirection(cmd, env))
		exec->exit = 1;
	if (build_argv(exec, cmd, env))
		exec->exit = 1;
	return (exec->exit);
}

int	execute_pipex_init(t_execute *exec, t_node *pipex, t_node *cmd,
		t_myenv *env)
{
	if (!exec || !pipex || !cmd)
		return (errno = ENODATA, 1);
	if (cmd->next_sibling)
	{
		if (pipe(pipex->fd) == SYS_FAIL)
			return (exec->exit = 1, perror("pipe"), 1);
		cmd->fd[OUT] = pipex->fd[OUT];
		cmd->next_sibling->fd[IN] = pipex->fd[IN];
		exec->toclose_child = pipex->fd[IN];
	}
	else
		exec->toclose_child = -1;
	if (cmd->type == NODE_BRACKET)
	{
		exec->bracket_first_child = cmd->first_child;
		return (0);
	}
	if (execute_cmd_init(exec, cmd, env))
		return (1);
	else
		return (0);
}

void	wait_cmd(t_execute *exec, t_node *cmd)
{
	int	status;

	status = 0;
	if (!exec || !cmd)
		return (errno = ENODATA, (void) NULL);
	if (waitpid(cmd->pid, &status, 0) == cmd->pid && WIFEXITED(status))
		cmd->exit = WEXITSTATUS(status);
	else
		cmd->exit = exec->exit;
	if (!WIFSIGNALED(status))
		return ;
	if (WTERMSIG(status) == SIGINT)
		cmd->exit = 130;
	if (WTERMSIG(status) == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		cmd->exit = 131;
	}
}

void	wait_pipex(t_execute *exec, t_node *pipex)
{
	int		status;
	t_node	*cmd;

	if (!exec || !pipex)
		return (errno = ENODATA, (void) NULL);
	cmd = pipex->first_child;
	while (cmd->next_sibling)
	{
		if (cmd->pid != -1)
			waitpid(cmd->pid, &status, 0);
		cmd = cmd->next_sibling;
	}
	if (waitpid(cmd->pid, &status, 0) == cmd->pid && WIFEXITED(status))
		pipex->exit = WEXITSTATUS(status);
	else
		pipex->exit = exec->exit;
	if (!WIFSIGNALED(status))
		return ;
	if (WTERMSIG(status) == SIGINT)
		pipex->exit = 130;
	if (WTERMSIG(status) == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		pipex->exit = 131;
	}
}
