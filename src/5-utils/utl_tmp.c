/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_tmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:14:05 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 22:43:51 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/signal_not_libc.h"

char	*get_tmp_file(char *dir)
{
	static const char	*basename = "/temp_buffer_hd_";
	char				*file;
	char				*path;
	int					inc;

	if (!dir)
		return (NULL);
	file = ft_strjoin(dir, basename);
	if (!file)
		return (NULL);
	inc = 0;
	path = ft_strjoin2(file, ft_itoa(inc), 0, 1);
	while (path && access(path, F_OK) == 0 && ++inc < DOC_MAXFILES)
	{
		free(path);
		path = ft_strjoin2(file, ft_itoa(inc), 0, 1);
	}
	free(file);
	return (path);
}

char	*get_tmp_path(t_myenv *env)
{
	char	*dir;
	char	*ret;

	ret = NULL;
	if (!access("/tmp", F_OK | W_OK | R_OK))
		ret = get_tmp_file("/tmp");
	dir = var_get_value(env->lst_var, "HOME");
	if (!ret && dir && !access(dir, F_OK | W_OK | R_OK))
		ret = get_tmp_file(dir);
	dir = var_get_value(env->lst_var, "PWD");
	if (!ret && dir && !access(dir, F_OK | W_OK | R_OK))
		ret = get_tmp_file(dir);
	dir = NULL;
	if (!ret)
		dir = ft_readline("Please enter filepath > ", handler_heredoc, SIG_IGN);
	if (!ret && dir && !access(dir, F_OK | W_OK | R_OK))
		ret = get_tmp_file(dir);
	if (dir)
		free(dir);
	if (!ret)
		ft_dprintf(2, "minishell: heredoc: Oh, c'mon... %s\n", strerror(errno));
	return (ret);
}

int	get_tmp(t_myenv *env)
{
	static char	*path = NULL;
	static int	fd = -1;

	if (!env)
	{
		if (path && fd > 0)
			close(fd);
		if (path)
			free(path);
		return (fd = -1, path = NULL, -1);
	}
	if (path)
	{
		if (fd > 0)
			close(fd);
		fd = open(path, O_RDONLY);
		unlink(path);
		free(path);
		return (path = NULL, fd);
	}
	path = get_tmp_path(env);
	if (!path)
		return (-1);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	return (fd);
}
