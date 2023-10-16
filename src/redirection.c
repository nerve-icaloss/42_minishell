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

void	reset_redirection(t_execute *exec)
{
}

void	close_redirection(t_execute *exec, int fd)
{
	if (exec->redir[fd] > 0)
	{
		if (close(exec->redir[fd]))
			perror("close");
		exec->redir[fd] = -2;
	}
}

int	apply_redirection(t_execute *exec)
{
	if (exec->redir[IN] > -1)
	{
		if (dup2(exec->redir[IN], 0) == SYS_FAIL)
			return (perror("dup2"), 1);
		close_redirection(exec, IN);
	}
	if (exec->redir[OUT] > -1)
	{
		if (dup2(exec->redir[OUT], 0) == SYS_FAIL)
			return (perror("dup2"), 1);
		close_redirection(exec, OUT);
	}
	return (0);
}

int	infile_redirection(t_execute *exec, t_node *cmd)
{
	t_node	*child;
	t_node	*i;
	
	if (!exec || !cmd)
		return (errno =ENODATA, 1);
	exec->redir[IN] = -2;
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->redir == READ || child->redir == HEREDOC)
			close_prev_redirection(exec, IN);
		if (child->redir == READ)
			exec->redir[IN] = open_read(child->val);
		if (child->redir == HEREDOC)
			exec->redir[IN] = child->fd;
		if (exec->redir[IN] == SYS_FAIL)
			return (perror(child->val), 1);
		node_sibling_pop(child);
		child = i;
	}
	return (0);
}

int	outfile_redirection(t_execute *exec, t_node *cmd)
{
	t_node	*child;
	t_node	*i;
	
	if (!exec || !cmd)
		return (errno =ENODATA, 1);
	exec->redir[OUT] = -2;
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->redir == TRUNC || child->redir == APPEND)
			close_prev_redirection(exec, OUT);
		if (child->redir == TRUNC)
			exec->redir[OUT] = open_trunc(child->val);
		if (child->redir == APPEND)
			exec->redir[OUT] = open_append(child->val);
		if (exec->redir[OUT] == SYS_FAIL)
			return (perror(child->val), 1);
		node_sibling_pop(child);
		child = i;
	}
	return (0);
}
