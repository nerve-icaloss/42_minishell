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

#include "builtin.h"

int	is_builtin(char *str)
{
	if (ft_strncmp("pwd", str, 3) && ft_strlen(str) == 3)
		return (1);
	if (ft_strncmp("cd", str, 2) && ft_strlen(str) == 2)
		return (1);
	if (ft_strncmp("env", str, 3) && ft_strlen(str) == 3)
		return (1);
	if (ft_strncmp("export", str, 6) && ft_strlen(str) == 6)
		return (1);
	if (ft_strncmp("unset", str, 5) && ft_strlen(str) == 5)
		return (1);
	if (ft_strncmp("echo", str, 3) && ft_strlen(str) == 3)
		return (1);
	if (ft_strncmp("exit", str, 5) && ft_strlen(str) == 5)
		return (1);
	return (0);
}

int	choose_function(t_execute *exec, t_myshell *shell)
{
	int	exit;

	if (ft_strncmp("pwd", str, 3) && ft_strlen(str) == 3)
		exit = pwd_builtin(cmd->args, &shell->env);
	if (ft_strncmp("cd", cmd->name, 2) && ft_strlen(cmd->name) == 2)
		exit = cd_builtin(cmd->args, &shell->env);
	if (ft_strncmp("echo", cmd->name, 3) && ft_strlen(cmd->name) == 3)
		exit = echo_builtin(cmd->args);
	if (ft_strncmp("env", cmd->name, 3) && ft_strlen(cmd->name) == 3)
		exit = env_builtin(&shell->env);
	if (ft_strncmp("export", cmd->name, 6) && ft_strlen(cmd->name) == 6)
		exit = export_builtin(cmd->args, &shell->env);
	if (ft_strncmp("unset", cmd->name, 5) && ft_strlen(cmd->name) == 5) //TODO prendre env en argument
		exit = unset_builtin(cmd->args, &shell->env.lst_var);
	if (ft_strncmp("exit", cmd->name, 5) && ft_strlen(cmd->name) == 5)
		exit = exit_builtin(cmd->args, &shell->env);
	if (shell->env.subsh)
		shell_clean(shell);
	return (exit);
}
