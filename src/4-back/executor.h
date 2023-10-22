/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:38:28 by nserve            #+#    #+#             */
/*   Updated: 2023/10/17 13:38:30 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../headers/minishell.h"

int execute_cmd(t_node *cmd, t_myshell *shell);
int execute_pipex(t_node *pipex, t_myshell *shell);
int stop_execute(t_node *node, int exit);
int execute_tree(t_node *root, t_myshell *shell);

#endif
