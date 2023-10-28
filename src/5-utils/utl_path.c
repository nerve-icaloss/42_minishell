/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 22:35:04 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 11:05:08 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_path(char *path)
{
	t_stat	dir;

	if (*path == '\0')
	{
		if (stat("/", &dir))
			return (0);
	}
	else
		if (stat(path, &dir))
			return (0);
	return (dir.st_mode & S_IXUSR);
}

/*
 * trim path to last not fail
 * */
int	check_whole_path(char *path)
{
	char	*i;
	char	*prev;

	prev = path;
	i = ft_strchr(path, '/');
	while (i && *i)
	{
		*i = '\0';
		if (!check_path(path))
			return (*prev = '\0', 0);
		*i = '/';
		prev = i;
		i = ft_strchr(i + 1, '/');
	}
	if (check_path(path))
		return (1);
	return (*prev = '\0', 0);
}

char	*ft_getcwd(t_myenv *env)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (ret)
		return (ret);
	return (ft_strdup(var_get_value(env->lst_var, "PWD")));
}
