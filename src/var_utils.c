/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 10:44:45 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	var_clean(t_lstvar *lst)
{
	t_lstvar	i;

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
 *   - add_var DOES NOT free name nor value in case of crash
 * */
int	var_add(t_lstvar *origin, char *name, char *value)
{
	t_myvar	*to_add;

	if (!name || !origin)
		return (-1);
	to_add = malloc(sizeof(t_myvar));
	if (!to_add)
		return (-1);
	to_add->name = name;
	to_add->value = value;
	if (*origin)
		(*origin)->prev = to_add;
	to_add->next = *origin;
	to_add->prev = NULL;
	*origin = to_add;
	return (0);
}

