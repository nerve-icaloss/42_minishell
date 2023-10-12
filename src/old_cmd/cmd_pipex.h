/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:29:54 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 10:30:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PIPEX_H
# define CMD_PIPEX_H

# include "../headers/minishell.h"

int pipex_cmd(t_cmdtab *cmd_tab, int cmd_count, t_myshell *shell);
void pipex_child(t_cmdtab *cmd_tab, int pipe_fd[2], int cmd_id, t_myshell *shell);
int pipex_parent(t_cmdtab *cmd_tab, t_myshell *shell);

#endif
