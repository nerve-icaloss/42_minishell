/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:41:37 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 12:41:41 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_pipe.h"

int	init_pipe(int **pipe_fd)
{
	*pipe_fd = malloc(sizeof(*pipe_fd) * 2);
	if (!*pipe_fd)
		return (SYS_FAIL);
	return (0);
}

int	open_pipe(t_cmdtab *cmdtab, int **pipe_fd, int cmd_count, int id)
{
	if (id < cmd_count - 1)
	{
		if (pipe(*pipe_fd) == SYS_FAIL)
			return (SYS_FAIL);
		cmdtab[id]->out_fd = *pipe_fd[1];
		cmdtab[id + 1]->in_fd = *pipe_fd[0];
	}
	return (0);
}

int	close_child_pipe(int pipe_fd[2], int cmd_id, int cmd_count)
{
	if (cmd_id < cmd_count - 1)
	{
		if (close(pipe_fd[0]) == SYS_FAIL)
			return (perror("close_pipe"), SYS_FAIL);
	}
	return (0);
}

int	close_parent_pipe(t_cmdtab *cmdtab, int pipe_fd[2], int id, int count)
{
	if (id > 0)
	{
		if (close(cmdtab[id]->in_fd) == SYS_FAIL)
			return (perror("close_pipe "), SYS_FAIL);
	}
	if (id < count - 1)
	{
		if (close(pipe_fd[1]) == SYS_FAIL)
			return (perror("close_pipe"), SYS_FAIL);
	}
	return (0);
}
