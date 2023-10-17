/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:54:16 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 17:54:21 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "open_utils.h"
#include <asm-generic/errno.h>
#include <stdio.h>
#include <unistd.h>

static void	close_redirection(t_node *cmd, int fd)
{
	if (cmd->fd[fd] > 0)
	{
		if (close(cmd->fd[fd]))
			perror("close");
		cmd->fd[fd] = -1;
	}
}

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
		close_redirection(cmd, IN);
	}
	if (cmd->fd[OUT] > -1)
	{
		exec->std_fd[OUT] = dup(STDOUT_FILENO);
		if (exec->std_fd[OUT] == -1)
			return (perror("dup"), 1);
		if (dup2(cmd->fd[OUT], STDOUT_FILENO) == SYS_FAIL)
			return (perror("dup2"), STDOUT_FILENO);
		close_redirection(cmd, OUT);
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

int	infile_redirection(t_node *cmd)
{
	t_node	*child;
	t_node	*i;
	
	if (!cmd)
		return (errno =ENODATA, 1);
	cmd->fd[IN] = -2;
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->rtype == READ || child->rtype == HEREDOC)
			close_redirection(cmd, IN);
		if (child->rtype == READ)
			cmd->fd[IN] = open_read(child->val);
		if (child->rtype == HEREDOC)
			cmd->fd[IN] = child->fd[IN];
		if (cmd->fd[IN] == SYS_FAIL)
			return (perror(child->val), 1);
		node_sibling_pop(child);
		child = i;
	}
	return (0);
}

int	outfile_redirection(t_node *cmd)
{
	t_node	*child;
	t_node	*i;
	
	if (!cmd)
		return (errno =ENODATA, 1);
	cmd->fd[OUT] = -2;
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->rtype == TRUNC || child->rtype == APPEND)
			close_redirection(cmd, OUT);
		if (child->rtype == TRUNC)
			cmd->fd[OUT] = open_trunc(child->val);
		if (child->rtype == APPEND)
			cmd->fd[OUT] = open_append(child->val);
		if (cmd->fd[OUT] == SYS_FAIL)
			return (perror(child->val), 1);
		node_sibling_pop(child);
		child = i;
	}
	return (0);
}
