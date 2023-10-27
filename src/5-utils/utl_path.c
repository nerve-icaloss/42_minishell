/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 22:35:04 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/27 22:53:22 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_path(char *path)
{
	t_stat	dir;

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
		*i = '\0';
		if (!check_path(path))
			return (*i = '/', 0);
		*i = '/';
		i = ft_strchr(i + 1, '/');
	}
	return (check_path(path));
}
