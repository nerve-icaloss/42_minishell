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

#include "blt_cd.h"

int	path_arg_parser(char **argv, t_myenv *myenv, char **path)
{
	if (!argv || !*argv)
		return (-1);
	if (!argv[1])
		*path = myenv->home->value;
	else if (argv[2])
		return (ft_dprintf(2, "cd: TOO MANY ARGUMENTS\n"), 1);
	else if (ft_strlen(argv[1]) == 1 && *argv[1] == '-')
	{
		if (!myenv->oldpwd || !myenv->oldpwd->value)
			return (ft_dprintf(2, "cd: OLDPWD not set\n"), 1);
		*path = myenv->oldpwd->value;
	}
	else
		*path = argv[1];
	if (**path == '\0')
	{
		if (!myenv->home || !myenv->home->value)
			return (ft_dprintf(2, "cd: HOME not set\n"), 1);
		*path = myenv->home->value;
	}
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
	var_add(&myenv->lst_var, ft_strdup("OLDPWD"), ft_strdup(
				var_get_value(myenv->lst_var, "PWD")));
	var_add(&myenv->lst_var, ft_strdup("PWD"), path);
	return (0);
}
