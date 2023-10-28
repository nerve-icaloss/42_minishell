/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 22:35:04 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 11:54:02 by hmelica          ###   ########.fr       */
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

int	check_whole_path(char *path)
{
	char	*i;

	i = ft_strchr(path, '/');
	while (i && *i)
	{
		if (!check_path(path))
			return (*i = '/', 0);
		*i = '/';
		i = ft_strchr(i + 1, '/');
	}
	return (check_path(path));
}

char	*ft_getcwd(t_myenv *env)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (ret)
		return (ret);
	return (ft_strdup(var_get_value(env->lst_var, "PWD")));
}
