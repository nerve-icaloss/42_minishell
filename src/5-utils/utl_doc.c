/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:11:19 by nserve            #+#    #+#             */
/*   Updated: 2023/10/27 11:11:39 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/expander.h"

t_myenv	*expand_this_doc(char **val, t_myenv *env)
{
	long	i;

	i = -1;
	if (*val[0] == '\'' || *val[0] == '"')
	{
		i = find_closing_quote(*val);
		*val[i] = '\0';
		ft_offset(*val, 1);
		return (NULL);
	}
	else
		return (env);
}

void	write_doc_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	doc_happend(char *line, char *eof, int write_fd, t_myenv *env)
{
	int		len[2];

	len[0] = ft_strlen(eof);
	len[1] = ft_strlen(line);
	if (!(line && (len[1] != len[0] || ft_strncmp(line, eof, len[0]) != 0)))
		return (0);
	if (env)
		var_expansion(&line, env);
	if (!line)
		return (-2);
	write_doc_pipe(write_fd, line);
	free(line);
	return (2);
}
