/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:24:42 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 14:24:44 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "error.h"

char	*get_cmd_path(char *name, t_myshell *shell)
{
	char	**paths;
	char	*cmd_path;

	if (name[0] == '/' || name[0] == '.')
		return (name);
	paths = ft_split(shell->env.path->value, ':');
	if (!paths)
		return (path_notfound(), NULL);
	cmd_path = find_cmd_path(name, paths);
	return (ft_arrclear(paths), cmd_path);
}

char	*find_cmd_path(char *name, char *paths[])
{
	char	*path;
	char	*file;
	int		i;

	i = 0;
	path = NULL;
	if (name[0] == '\0')
		return (path);
	file = ft_strjoin("/", name);
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], file);
		if (access(path, F_OK | X_OK) == -1)
		{
			free(path);
			path = NULL;
		}
		else
			break ;
	}
	free(file);
	return (path);
}

int	search_path(t_execute *exec)
{
	return (0);
}
