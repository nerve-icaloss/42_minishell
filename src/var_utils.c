/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 16:40:55 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
 * t_done */
void	var_clean(t_lstvar *lst)
{
	t_lstvar	i;

	if (!lst)
		return ;
	i = *lst;
	while (i)
	{
		*lst = (*lst)->next;
		free(i->name);
		if (i->value)
			free(i->value);
		free(i);
		i = *lst;
	}
	*lst = NULL;
}

/*
 * Description :
 * Add var name=value to origin.
 *   - Crash if no name
 *   - name and value should be malloc'd (or value can be NULL)
 *   - var_add DOES NOT free name nor value in case of crash
 * -1 means an error and programm should crash
 * t_done */
int	var_add(t_lstvar *origin, char *name, char *value)
{
	t_myvar	*to_add;
	int		len;

	if (!name || !origin)
		return (-1);
	len = ft_strlen(name);
	to_add = *origin;
	while (to_add && ft_strncmp(name, to_add->name, len) != 0)
		to_add = to_add->next;
	if (!to_add)
		to_add = malloc(sizeof(t_myvar));
	else
		len = 0;
	if (!to_add)
		return (-1);
	to_add->name = name;
	to_add->value = value;
	if (len)
		return (0);
	if (*origin)
		(*origin)->prev = to_add;
	to_add->next = *origin;
	to_add->prev = NULL;
	*origin = to_add;
	return (0);
}

