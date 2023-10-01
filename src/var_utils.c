/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 14:12:45 by hmelica          ###   ########.fr       */
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

void	var_update(t_lstvar var, char *name, char *value)
{
	if (var->name != name)
		free(var->name);
	if (value)
		free(var->value);
	var->name = name;
	var->value = value;
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
	size_t		len;

	if (!name || !origin)
		return (-1);
	len = ft_strlen(name);
	to_add = *origin;
	while (to_add && (ft_strncmp(name, to_add->name, len) != 0 || len
			!= ft_strlen(to_add->name)))
		to_add = to_add->next;
	if (!to_add)
		to_add = malloc(sizeof(t_myvar));
	else
		return (var_update(to_add, name, value), 0);
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

/*
 * pop lst item and handle link between next and prev
 * origin is there to handle the case of lst being origin
 * origin can be set to NULL if not needed
 * */
int	var_pop(t_lstvar *origin, t_lstvar lst)
{
	if (!lst)
		return (-1);
	if (origin && *origin == lst)
		*origin = lst->next;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	lst->next = NULL;
	lst->prev = NULL;
	var_clean(&lst);
	return (0);
}
