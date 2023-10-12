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

#include "../../headers/minishell.h"

int	entry_add(t_history *origin, char *str)
{
	t_myentry	*to_add;

	if (!origin || !str)
		return (-1);
	add_history(str);
	to_add = *origin;
	while (to_add)
		to_add = to_add->next;
	to_add = malloc(sizeof(*to_add));
	if (!to_add)
		return (-1);
	to_add->content = ft_strdup(str);
	to_add->next = NULL;
	return (0);
}

void	history_clean(t_history *origin)
{
	t_myentry	*i;

	if (!*origin)
		return ;
	i = *origin;
	while (i)
	{
		*origin = (*origin)->next;
		free(i->content);
		free(i);
		i = *origin;
	}
	*origin = NULL;
}
