/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:27:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 12:27:08 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"
#include "redirection.h"

int	execute_pipe_init(t_execute *exec, int pipe[2], t_node *cmd)
{

	return (0);
}

int	execute_cmd_init(t_execute *exec, t_node *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == SYS_FAIL)
		return (1);
	return (0);
}
