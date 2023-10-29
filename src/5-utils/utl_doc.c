/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:11:19 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 22:11:29 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/expander.h"
#include "../../headers/here_doc.h"
#include "../../headers/signal_not_libc.h"

int	expand_this_doc(char **val)
{
	long	i;

	i = -1;
	if (*val[0] == '\'' || *val[0] == '"')
	{
		i = find_closing_quote(*val);
		*val[i] = '\0';
		ft_offset(*val, 1);
		return (0);
	}
	return (1);
}

char	*get_tmp_file(char *dir)
{
	static const char	*basename = "/temp_buffer_hd";
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
	if (access("/tmp", F_OK | W_OK | R_OK))
		ret = get_tmp_file("/tmp");
	dir = var_get_value(env->lst_var, "HOME");
	if (!ret && dir && access(dir, F_OK | W_OK | R_OK))
		ret = get_tmp_file(dir);
	dir = var_get_value(env->lst_var, "PWD");
	if (!ret && dir && access(dir, F_OK | W_OK | R_OK))
		ret = get_tmp_file(dir);
	dir = NULL;
	if (!ret)
		dir = ft_readline("Please enter filepath > ", handler_heredoc, SIG_IGN);
	if (!ret && dir && access(dir, F_OK | W_OK | R_OK))
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
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT);
	return (fd);
}

void	write_doc_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	is_eof(char *eof, char *line)
{
	size_t	len[2];

	if (!eof || !line)
		return (-1);
	len[0] = ft_strlen(eof);
	len[1] = ft_strlen(line);
	if (!(line && (len[1] != len[0] || ft_strncmp(line, eof, len[0]) != 0)))
		return (1);
	return (0);
}

int	here_done(char *buffer, t_myenv *env)
{
	int	fd[2];

	if (buffer)
	{
		if (pipe(fd))
			return (free(buffer), -1);
		write_doc_pipe(fd[1], buffer);
		free(buffer);
		close(fd[1]);
		return (get_tmp(NULL), fd[0]);
	}
	return (get_tmp(env));
}

int	put_in_buffer(char **buffer, char **line, t_myenv *env, int ret[2])
{
	if (ret[1])
		var_expansion(line, env);
	if (ft_strlen(*line) + ft_strlen(*buffer) < DOC_BUF - 1)
		return (-!(ft_strlcat(*buffer, *line, DOC_BUF) < DOC_BUF
					&& ft_strlcat(*buffer, "\n", DOC_BUF) < DOC_BUF));
	if (ret[0] < 0)
	{
		ret[0] = get_tmp(env);
		write_doc_pipe(ret[0], *buffer);
		free(*buffer);
		*buffer = NULL;
	}
	if (ret[0] < 0)
		return (-1);
	write_doc_pipe(ret[0], *line);
	return (ret[0]);
}

/*
int	doc_append(char *line, char *eof, char *buffer, t_myenv *env)
{
	int		len[2];
	int		fd;

	if (!line)
		return (-2);
	if (*buffer)
	{
		fd = get_tmp(env);
		if (fd <= 0)
			return (-2);
	}
	free(line);
	return (2);
}
*/
