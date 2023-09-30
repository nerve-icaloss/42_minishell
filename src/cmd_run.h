/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:55:25 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 18:55:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_RUN_H
# define CMD_RUN_H

# include "../headers/minishell.h"

int single_cmd(t_mycmd *cmd, t_myshell *shell);
int single_builtin(t_mycmd *cmd, t_myshell *shell);
void single_child(t_mycmd *cmd, t_myshell *shell);
int single_parent(t_mycmd *cmd, t_myshell *shell);
void run_cmd(t_mycmd *cmd, t_myshell *shell);

#endif
