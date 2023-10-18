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

int find_builtin_f(t_execute *exec);

int	pwd_builtin(char *argv[],t_myenv *env);
int	cd_builtin(char *argv[], t_myenv *env);
int	env_builtin(t_myenv *env);
int	export_builtin(char *argv[], t_myenv *env);
int	unset_builtin(char *argv[], t_lstvar *lst);
int	echo_builtin(char *argv[]);
int	exit_builtin(char *argv[], t_myenv *env);

#endif
