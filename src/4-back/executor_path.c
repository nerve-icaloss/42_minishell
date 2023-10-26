/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:24:42 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:14:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <asm-generic/errno-base.h>
#include <sys/stat.h>

static char	*scan_dirs(char *data)
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
			buf++;
			return (ret);
		}
		buf++;
	}
	return (ret);
}

static char	**split_dirs(char *data, int size)
{
	char	**dirs;
	char	*path;
	int		len;
	int		i;

	if (!data)
		return (errno = ENODATA, NULL);
	dirs = malloc(sizeof(char *) * (size + 1));
	if (!dirs)
		return (errno = ENOMEM, NULL);
	path = scan_dirs(data);
	i = 0;
	while (*path)
	{
		len = ft_strlen(path);
		dirs[i] = malloc(sizeof(char) * (len + 2));
		if (!dirs[i])
			return (ft_arrclear(dirs), NULL);
		ft_memset(dirs[i], 0, (len + 2));
		ft_strlcat(dirs[i], path, len + 1);
		ft_strlcat(dirs[i], "/", len + 2);
		path = scan_dirs(NULL);
		i++;
	}
	return (dirs);
}

static char	*scan_dirs_cmdfile(char *name, char *dirs[])
{
	char		*path;
	char		*cwd;
	struct stat	sb;
	int			i;

	path = NULL;
	cwd = getcwd(NULL, 0);
	i = -1;
	while (dirs[++i])
	{
		if (chdir(dirs[i]) == SYS_FAIL)
			continue ;
		if (stat(name, &sb) == 0 && sb.st_mode && S_ISREG(sb.st_mode))
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
	t_myvar	*path;

	if (!name || !env)
		return (errno = ENODATA, NULL);
	path = var_get(env->lst_var, "PATH");
	if (!path)
		return (errno = ENODATA, NULL);
	i = -1;
	size = 1;
	while (path->value[++i])
	{
		if (path->value[i] == ':')
			size++;
	}
	cmd_path = ft_strdup(path->value);
	dirs = split_dirs(cmd_path, size);
	free(cmd_path);
	if (!dirs)
		return (free(cmd_path), NULL);
	cmd_path = scan_dirs_cmdfile(name, dirs);
	return (ft_arrclear(dirs), cmd_path);
}

int	check_cmd_path(t_execute *exec, char *name)
{
	struct stat	sb;

	if (name[0] == '.' && name[1] != '/')
	{
		ft_dprintf(2, "minishell: %s: filename argument required\n", name);
		exec->exit = 1;
		return (1);
	}
	if (stat(name, &sb) == 0 && sb.st_mode && S_ISDIR(sb.st_mode))
	{
		errno = EISDIR;
		perror(name);
		exec->exit = 126;
		return (1);
	}
	return (0);
}
