/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:11:19 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 23:48:27 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/expander.h"
#include "../../headers/here_doc.h"

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

int	here_done(int ret, char *buffer, t_myenv *env)
{
	int	fd[2];

	if (ret <= 0)
	{
		if (pipe(fd))
			return (free(buffer), -2);
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
	if (ret[0] < 0 && ft_strlen(*line) + ft_strlen(*buffer) < DOC_BUF - 1)
		return (ft_strlcat(*buffer, *line, DOC_BUF),
				ft_strlcat(*buffer, "\n", DOC_BUF), -2);
	if (ret[0] < 0)
	{
		ret[0] = get_tmp(env);
		if (ret[0] < 0)
			return (-2);
		write(ret[0], *buffer, ft_strlen(*buffer));
		*buffer = ft_memset(*buffer, '\0', DOC_BUF);
	}
	if (ret[0] < 0)
		return (-1);
	write_doc_pipe(ret[0], *line);
	return (ret[0]);
}
