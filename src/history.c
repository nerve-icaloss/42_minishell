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
#include "utils_open.h"

void	load_history(void)
{
	int		fd;
	char	*buffer;
	char	*history;

	fd = open(HISTORY_FILE, O_RDONLY, 000666);
	if (fd == -1)
		return (perror("register"));
	buffer = get_next_line(fd);
	while (buffer)
	{
		history = ft_substr(buffer, 0, ft_strlen(buffer) - 1);
		add_history(history);
		free(history);
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
