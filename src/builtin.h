/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:13:52 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 17:15:25 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

# include "../headers/minishell.h"

int is_builtin(char *str);
int run_builtin(t_execute *exec, t_myshell *shell);

int	pwd_builtin(t_myenv *env);
int	cd_builtin(char *args[], t_myenv *env);
int	env_builtin(t_myenv *env);
int	export_builtin(char *args[], t_myenv *env);
int	unset_builtin(char *args[], t_lstvar *lst);
int	echo_builtin(char *args[]);
int	exit_builtin(char *args[], t_myenv *env);

#endif
