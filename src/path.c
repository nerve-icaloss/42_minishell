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

char	*scan_dirs(char *data)
{
	static char	*buf;
	char		*ret;

	if (data)
		buf = data;
	while (*buf == ':')
		buf++;
	ret = buf;
	while (*buf)
	{
		if (*buf == ':')
		{
			*buf = '\0';
			return (ret);
		}
		buf++;
	}
	return (ret);
}

void	split_dirs(char ***dirs, char *data)
{
	char	*path;
	int		i;

	if (!dirs || !data)
		return (errno = ENODATA, (void)NULL);
	path = 	scan_dirs(data);
	i = 0;
	while (*path)
	{
		*dirs[i] = malloc(sizeof(char) * (ft_strlen(path) +1));
		if (!*dirs[i])
			return (ft_arrclear(*dirs), *dirs = NULL, (void)NULL);
		*dirs[i] = ft_strjoin(*dirs[i], path);
		*dirs[i] = ft_strjoin(*dirs[i], "/");
		path = scan_dirs(NULL);
		i++;
	}
}

char	*scan_dirs_cmdfile(char *name, char *dirs[])
{
	char		*path;
	char		*cwd;
	struct stat	sb;
	int			i;

	path = NULL;
	cwd = getcwd(NULL, 0);
	i = 0;
	while (dirs[i])
	{
		if (chdir(dirs[i]) == SYS_FAIL)
		{
			perror("dirs[i]");
			continue ;
		}
		if (stat(name, &sb) && sb.st_mode && S_ISREG(sb.st_mode))
		{
			path = ft_strjoin(dirs[i], name);
			break ;
		}
	}
	if (chdir(cwd) == SYS_FAIL)
		perror(cwd);
	return (free(cwd), path);
}

char	*search_cmd_path(char *name, t_myenv *env)
{
	char	**dirs;
	char	*cmd_path;
	int		size;
	int		i;

	if (!name || !env)
		return (errno = ENODATA, NULL);
	i = 0;
	size = 0;
	while (env->path->value[i])
	{
		if (env->path->value[i] == ':')
			size++;
		i++;
	}
	dirs = malloc(sizeof(*dirs) * (size + 1));
	if (!dirs)
		return (errno = ENOMEM, NULL);
	ft_memset(dirs, 0, sizeof(char *));
	split_dirs(&dirs, name);
	if (!dirs)
		return (NULL);
	cmd_path = scan_dirs_cmdfile(name, dirs);
	return (ft_arrclear(dirs), cmd_path);
}
