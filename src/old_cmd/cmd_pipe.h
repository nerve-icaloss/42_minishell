/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 09:44:00 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 09:44:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PIPE_H
# define CMD_PIPE_H

# include "../headers/minishell.h"

int	init_pipe(int **pipe_fd);
int open_pipe(t_cmdtab *cmdtab, int *pipe_fd[2], int i, int count);
int close_child_pipe(int pipe_fd[2], int i, int count);
int close_parent_pipe(t_cmdtab *cmdtab, int pipe_fd[2], int i, int count);

#endif
