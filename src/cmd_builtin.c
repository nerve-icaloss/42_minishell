/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:51:15 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 17:51:18 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"

int	is_builtin(char *str)
{
	if (ft_strncmp("cd", str, 2) && ft_strlen(str) == 2)
		return (1);
	if (ft_strncmp("pwd", str, 3) && ft_strlen(str) == 3)
		return (1);
	if (ft_strncmp("env", str, 3) && ft_strlen(str) == 3)
		return (1);
	if (ft_strncmp("export", str, 6) && ft_strlen(str) == 6)
		return (1);
	if (ft_strncmp("unset", str, 5) && ft_strlen(str) == 5)
		return (1);
	if (ft_strncmp("exit", str, 5) && ft_strlen(str) == 5)
		return (1);
	return (0);
}

int	run_builtin(t_mycmd *cmd, t_myshell *shell)
{
	int	(*builtin)(char **av, t_myenv *env);
	int	exit;

	if (ft_strncmp("cd", cmd->name, 2) && ft_strlen(cmd->name) == 2)
		builtin = &cd;
	if (ft_strncmp("pwd", cmd->name, 3) && ft_strlen(cmd->name) == 3)
		builtin = &pwd;
	if (ft_strncmp("env", cmd->name, 3) && ft_strlen(cmd->name) == 3)
		builtin = &env;
	if (ft_strncmp("export", cmd->name, 6) && ft_strlen(cmd->name) == 6)
		builtin = &export;
	if (ft_strncmp("unset", cmd->name, 5) && ft_strlen(cmd->name) == 5)
		builtin = &unset;
	if (ft_strncmp("exit", cmd->name, 5) && ft_strlen(cmd->name) == 5)
		builtin = &blt_exit;
	exit = builtin(cmd->args, &shell->env);
	if (ft_atoi(shell->env.shlvl->value) > 1)
		clean_shell(shell);
	return (exit);
}
