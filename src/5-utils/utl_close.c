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

void	close_redirection(t_node *cmd, int fd)
{
	if (cmd->fd[fd] > 0)
	{
		if (close(cmd->fd[fd]))
			perror("close");
		cmd->fd[fd] = -1;
	}
}
