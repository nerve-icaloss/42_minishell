/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:59:24 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 10:59:25 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_myentry	*new_entry(const char *str)
{
	t_myentry	*entry;

entry = malloc(sizeof(*entry));
	if (!entry)
		return (NULL);
	entry->content = ft_strdup(str);
	entry->next = NULL;
	return (entry);
}

void	add_entry(t_history *history, t_myentry *entry)
{
	t_history	current;

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

void	clean_history(t_history *history)
{
	t_history	current;
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
