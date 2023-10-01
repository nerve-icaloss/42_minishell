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
int run_builtin(t_mycmd *cmd, t_myshell *shell);

int	unset_builtin(char **argv, t_lstvar *lst);
int	export_builtin(char **argv, t_myenv *env);
int	echo_builtin(char **argv);
int	env_builtin(t_myenv *env);
int	exit_builtin(char *argv[], t_myenv *env);
int	cd_builtin(char **argv, t_myenv *env);

#endif
