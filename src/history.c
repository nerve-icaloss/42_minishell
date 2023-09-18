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
#include "libft/libft.h"
#include <stdio.h>

t_myentry	*new_entry(const char *str)
{
	t_myentry	*entry;

	entry = malloc(sizeof(*entry));
	if (!entry)
		return (NULL);
//should I do a copy and free read str in prompt loop
	entry->content = ft_strdup(str);
	entry->next = NULL;
	return (entry);
}

void	ft_add_history(t_myhistory *history, t_myentry *entry)
{
	t_myhistory	current;

	current = NULL;
	add_history(entry->content);
	if (!*history)
	{
		*history = entry;
	}
	else
	{
		current = *history;
		while (current->next)
		{
			current = current->next;
		}
		current->next = entry;
	}
}

void	ft_clear_history(t_myhistory *history)
{
	t_myhistory	current;
	t_myentry	*todel;

	if (!*history)
		return ;
	current = *history;
	while (current)
	{
		todel = current;
		current = current->next;
		free(todel);
	}
	*history = NULL;
}

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

void	register_history(t_myhistory *history)
{
	int			fd;
	t_myhistory	current;
	char		*log;

	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_APPEND, 000666);
	if (fd == -1)
		return (perror("register"));
	current = *history;
	while (current)
	{
		log = ft_strjoin(current->content, "\n");
		write(fd, log, ft_strlen(log));
		free(log);
		current = current->next;
	}
	ft_clear_history(history);
	if (close(fd) == -1)
		return ;
}
