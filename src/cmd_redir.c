/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:30:15 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 10:31:54 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"
#include "cmd_error.h"
#include "open_utils.h"
#include <unistd.h>

//manage in function with or without pipe
int	input_redirection(t_mycmd *cmd)
{
	if (cmd->in_count)
	{
		if (open_loop(&cmd->in, cmd->in_count) == SYS_FAIL)
			return (SYS_FAIL);
		if (!(cmd->in_fd == -1) && close(cmd->in_fd))
			return (perror("close_pipe"), SYS_FAIL);
		cmd->in_fd = cmd->in[cmd->in_count - 1].fd;
		close_loop(&cmd->in, cmd->in_count);
	}
	if (!(cmd->in_fd == -1))
	{
		if (dup2(cmd->in_fd, 0) == SYS_FAIL)
			return (perror("dup2 "), SYS_FAIL);
		if (close(cmd->in_fd))
		{
			if (cmd->in_count)
				perror(cmd->in[cmd->in_count - 1].file);
			else
				perror("close_pipe");
		}
	}
	return (0);
}

int	output_redirection(t_mycmd *cmd)
{
	if (cmd->out_count)
	{
		if (open_loop(&cmd->out, cmd->out_count) == SYS_FAIL)
			return (SYS_FAIL);
		if (!(cmd->out_fd == -1) && close(cmd->out_fd))
			return (perror("close_pipe"), SYS_FAIL);
		cmd->out_fd = cmd->out[cmd->out_count - 1].fd;
		close_loop(&cmd->out,  cmd->out_count);
	}
	if (!(cmd->out_fd == -1))
	{
		if (dup2(cmd->out_fd, 1) == SYS_FAIL)
			return (perror("dup2 "), SYS_FAIL);
		if (close(cmd->out_fd))
		{
			if (cmd->out_count)
				perror(cmd->out[cmd->out_count - 1].file);
			else
				perror("close_pipe");
		}
	}
	return (0);
}

int	open_loop(t_redirtab *redirtab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (redirtab[i]->redir == o_doc || redirtab[i]->redir == o_read)
			redirtab[i]->fd = open_read(redirtab[i]->file);
		if (redirtab[i]->redir == o_append)
			redirtab[i]->fd = open_append(redirtab[i]->file);
		if (redirtab[i]->redir == o_trunc)
			redirtab[i]->fd = open_trunc(redirtab[i]->file);
		if (redirtab[i]->fd == SYS_FAIL)
			return (perror(redirtab[i]->file), SYS_FAIL);
		i++;
	}
	return (0);
}

void	close_loop(t_redirtab *redirtab, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (close(redirtab[i]->fd) == SYS_FAIL)
			perror(redirtab[i]->file);
		i++;
	}
}
