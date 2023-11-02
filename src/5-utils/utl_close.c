/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:20:56 by nserve            #+#    #+#             */
/*   Updated: 2023/10/24 14:21:15 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_redirection(t_node *cmd, int mode)
{
	if (cmd->fd[mode] > 0)
	{
		if (close(cmd->fd[mode]) == SYS_FAIL)
			perror("close");
		cmd->fd[mode] = -1;
	}
}

void	close_pipe_in(t_node *cmd)
{
	if (cmd->fd[IN] > 0)
	{
		if (close(cmd->fd[IN]) == SYS_FAIL)
			perror("close");
		cmd->fd[IN] = -1;
	}
}
