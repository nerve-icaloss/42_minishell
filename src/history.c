/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:44:29 by marvin            #+#    #+#             */
/*   Updated: 2023/09/15 14:20:27 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "open_utils.h"

void	load_history(void)
{
	int		fd;
	char	*buffer;
	char	*nl;

	fd = open(HISTORY_FILE, O_RDONLY, 000666);
	if (fd == -1)
		return (perror("register"));
	buffer = get_next_line(fd);
	while (buffer)
	{
		nl = ft_strchr(buffer, '\n');
		if (nl)
			*nl = '\0';
		add_history(buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	if (close(fd) == -1)
		return ;
}

void	register_history(t_history *history)
{
	int			fd;
	t_history	i;
	char		*log;

	if (!history)
		return ;
	fd = open_append(HISTORY_FILE);
	if (fd == -1)
		return (perror(HISTORY_FILE));
	i = *history;
	while (i)
	{
		log = ft_strjoin(i->content, "\n");
		write(fd, log, ft_strlen(log));
		free(log);
		i = i->next;
	}
	rl_clear_history();
	history_clean(history);
	if (close(fd) == -1)
		return ;
}
