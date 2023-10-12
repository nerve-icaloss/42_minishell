/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:03 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/03 21:42:15 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Controle les arguments pour cd
 * */
int	path_arg_parser(char **argv, t_myenv *myenv, char **path)
{
	if (!argv || !*argv)
		return (-1);
	else if (argv[1] && argv[2])
		return (ft_dprintf(2, "cd: TOO MANY ARGUMENTS\n"), 1);
	else if (!argv[1])
	{
		if (!myenv->home || !myenv->home->value)
			return (ft_dprintf(2, "cd: HOME not set\n"), 1);
		*path = myenv->home->value;
	}
	else if (ft_strlen(argv[1]) == 1 && *argv[1] == '-')
	{
		if (!myenv->oldpwd || !myenv->oldpwd->value)
			return (ft_dprintf(2, "cd: OLDPWD not set\n"), 1);
		*path = myenv->oldpwd->value;
	}
	else
		*path = argv[1];
	return (0);
}

int	cd_builtin(char **argv, t_myenv *myenv)
{
	char	*path;

	if (path_arg_parser(argv, myenv, &path))
		return (1);
	if (access(path, F_OK))
		return (ft_dprintf(2, "cd: NO SUCH DIRECTORY"), 1);
	if (chdir(path))
		return (ft_dprintf(2, "cd: ERROR WHILE CHANGING DIRECTORY\n"), 1);
	path = getcwd(NULL, 0);
	if (!path)
		return (ft_dprintf(2, "cd: ERROR AFTER CHANGING DIRECTORY\n"), 1);
	if (!var_get(myenv->lst_var, "OLDPWD"))
		myenv->count++;
	if (!var_get(myenv->lst_var, "PWD"))
		myenv->count++;
	if (var_add(&myenv->lst_var, ft_strdup("OLDPWD"), ft_strdup(
			var_get_value(myenv->lst_var, "PWD"))) || var_add(&myenv->lst_var,
			ft_strdup("PWD"), path))
		return (-1);
	if (envp_update(myenv))
		return (ft_dprintf(2, "WARN: minor error while updating envp\n"), 0);
	return (0);
}
