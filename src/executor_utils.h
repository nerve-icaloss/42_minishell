/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:52:48 by nserve            #+#    #+#             */
/*   Updated: 2023/10/17 11:52:50 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "../headers/minishell.h"

int execute_pipex_init(t_execute *exec, t_node *pipex, t_node *cmd);
int execute_cmd_init(t_execute *exec, t_node *cmd);
void wait_cmd(t_execute *exec, t_node *cmd);
void wait_pipex(t_execute *exec, t_node *pipex);

#endif
