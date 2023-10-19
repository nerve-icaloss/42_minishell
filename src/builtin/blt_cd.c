/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:03 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/15 15:25:24 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Replace every tilde by home directory. Returns -1 if no home set.
 * Returns the count of tilde if more than one tildes found. That means :
 *  - 1 tilde found : returns 0
 *  - 0 tilde found : returns 0
 *  - x tildes found : returns x (because it is not always normal to
 *    expand more than one tilde)
 * ret should be set to NULL or to be malloc'd
 * */
int	home_expand(const char *s, char **ret, t_myenv *myenv)
{
	int		count;
	int		i;
	int		j;

	if (!s || !ret || !myenv || !myenv->home || !myenv->home->value)
		return (-1);
	i = 0;
	j = 0;
	count = 0;
	while (s && s[i + j])
	{
		while (s[i + j] && s[i + j] != '~')
			j++;
		*ret = ft_strjoin2(*ret, ft_substr(s, i, j), 1, 1);
		if (s[i + j] == '~' && ++i && ++count)
			*ret = ft_strjoin2(*ret, myenv->home->value, 1, 0);
		i += j;
		j = 0;
	}
	if (i == 0)
		return (*ret = ft_strdup(""), 0);
	if (count == 0 || count == 1 || !*ret)
		return (errno = ENOMEM * !*ret, -!*ret);
	return (count);
}

/*
 * Controle les arguments pour cd
 * */
int	path_arg_parser(char **argv, t_myenv *myenv, char **path)
{
	char	*s;

	if (!argv || !*argv)
		return (-1);
	else if (argv[1] && argv[2])
		return (ft_dprintf(2, "cd: TOO MANY ARGUMENTS\n"), 1);
	else if (!argv[1])
	{
		if (!myenv->home || !myenv->home->value)
			return (ft_dprintf(2, "cd: HOME not set\n"), 1);
		*path = myenv->home->value;
		return (0);
	}
	else if (ft_strlen(argv[1]) == 1 && *argv[1] == '-')
	{
		if (!myenv->oldpwd || !myenv->oldpwd->value)
			return (ft_dprintf(2, "cd: OLDPWD not set\n"), 1);
		*path = myenv->oldpwd->value;
		return (0);
	}
	s = NULL;
	if (home_expand(argv[1], &s, myenv) < 0)
		return (ft_dprintf(2, "cd: HOME not set\n"), 1);
	*path = s;
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
				var_get_value(myenv->lst_var, "PWD")))
		|| var_add(&myenv->lst_var, ft_strdup("PWD"), path))
		return (-1);
	if (envp_update(myenv))
		return (ft_dprintf(2, "WARN: minor error while updating envp\n"), 0);
	return (0);
}
