/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:38:28 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:43:02 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		pwd_builtin(char *argv[], t_myenv *env);
int		cd_builtin(char *argv[], t_myenv *env);
int		env_builtin(char *argv[], t_myenv *env);
int		export_builtin(char *argv[], t_myenv *env);
int		unset_builtin(char *argv[], t_myenv *env);
int		echo_builtin(char *argv[], t_myenv *env);
int		exit_builtin(char *argv[], t_myenv *env);

int		find_builtin_f(t_execute *exec);
char	*search_cmd_path(t_execute *exec, char *name, t_myenv *env);
char	*check_cmd_path(t_execute *exec, char *name);

int		execute_pipex_init(t_execute *exec, t_node *pipex, t_node *cmd,
			t_myenv *env);
int		execute_cmd_init(t_execute *exec, t_node *cmd, t_myenv *env);

void	child_cmd(t_execute *exec, t_myshell *shell);
void	child_pipex_cmd(t_execute *exec, t_myshell *shell);

void	wait_cmd(t_execute *exec, t_node *cmd);
void	wait_pipex(t_execute *exec, t_node *pipex);

int		execute_cmd(t_node *cmd, t_myshell *shell);
int		execute_pipex(t_node *pipex, t_myshell *shell);

int		stop_execute(t_node *node, int exit);
int		execute_tree(t_node *root, t_myshell *shell);

#endif
