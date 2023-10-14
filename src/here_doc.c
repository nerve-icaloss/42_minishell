/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:08:57 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/14 16:08:58 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
 * Use myenv == NULL to disable var_expansion
 * multiply by 1 or 0 if needed
 * line[1] is the line just readed and line[0] is all concatened lines.
 * */
int	here_doc(char *eof, t_myenv *myenv)
{
	int		len[2];
	int		fd[2];
	char	*line;

	(void) myenv;
	if (!eof || pipe(fd))
		return (-1);
	len[0] = ft_strlen(eof);
	line = readline("> ");
	len[1] = ft_strlen(line);
	while (line && (len[1] != len[0] || ft_strncmp(line, eof, len[0]) != 0))
	{
		if (myenv)
			var_expansion(&line, myenv);
		if (!line)
			break ;
		write(fd[1], line, len[1]);
		write(fd[1], "\n", 1);
		line = readline("> ");
		len[1] = ft_strlen(line);
	}
	close(fd[1]);
	if (!line)
		return (close(fd[0]), -1);
	return (fd[0]);
}
