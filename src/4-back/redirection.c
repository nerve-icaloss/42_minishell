/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:54:16 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:16:52 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/redirection.h"

int	apply_redirection(t_execute *exec, t_node *cmd)
{
	if (!exec || !cmd)
		return (errno = ENODATA, 1);
	if (cmd->fd[IN] > -1)
	{
		exec->std_fd[IN] = dup(STDIN_FILENO);
		if (exec->std_fd[IN] == -1)
			return (perror("dup"), 1);
		if (dup2(cmd->fd[IN], STDIN_FILENO) == SYS_FAIL)
			return (perror("dup2"), 1);
		if (close(cmd->fd[IN]) == SYS_FAIL)
			perror("close");
	}
	if (cmd->fd[OUT] > -1)
	{
		exec->std_fd[OUT] = dup(STDOUT_FILENO);
		if (exec->std_fd[OUT] == -1)
			return (perror("dup"), 1);
		if (dup2(cmd->fd[OUT], STDOUT_FILENO) == SYS_FAIL)
			return (perror("dup2"), STDOUT_FILENO);
		if (close(cmd->fd[OUT]) == SYS_FAIL)
			perror("close");
	}
	return (0);
}

int	reset_redirection(t_execute *exec, t_node *cmd)
{
	if (!exec || !cmd)
		return (errno = ENODATA, 1);
	if (cmd->fd[IN] > -1)
	{
		if (close(STDIN_FILENO) == SYS_FAIL)
			perror("close");
		if (dup2(exec->std_fd[IN], STDIN_FILENO) == SYS_FAIL)
			return (perror("dup2"), 1);
		if (close(exec->std_fd[IN]) == SYS_FAIL)
			perror("close");
	}
	if (cmd->fd[OUT] > -1)
	{
		if (close(STDOUT_FILENO) == SYS_FAIL)
			perror("close");
		if (dup2(exec->std_fd[OUT], STDOUT_FILENO) == SYS_FAIL)
			return (perror("dup2"), 1);
		if (close(exec->std_fd[OUT]) == SYS_FAIL)
			perror("close");
	}
	return (0);
}

int	infile_redirection(t_node *cmd, t_node *redir, t_myenv *env)
{
	close_redirection(cmd, IN);
	cmd->fd[IN] = open_redirection(redir, env);
	if (cmd->fd[IN] == SYS_FAIL)
		return (node_sibling_pop(redir), 1);
	return (node_sibling_pop(redir), 0);
}

int	outfile_redirection(t_node *cmd, t_node *redir, t_myenv *env)
{
	close_redirection(cmd, OUT);
	cmd->fd[OUT] = open_redirection(redir, env);
	if (cmd->fd[OUT] == SYS_FAIL)
		return (node_sibling_pop(redir), 1);
	return (node_sibling_pop(redir), 0);
}

int	do_redirection(t_node *cmd, t_myenv *env)
{
	t_node	*child;
	t_node	*i;

	if (!cmd)
		return (errno = ENODATA, 1);
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->rtype == READ || child->rtype == HEREDOC)
			if (infile_redirection(cmd, child, env))
				return (1);
		if (child->rtype == TRUNC || child->rtype == APPEND)
			if (outfile_redirection(cmd, child, env))
				return (1);
		child = i;
	}
	return (0);
}
