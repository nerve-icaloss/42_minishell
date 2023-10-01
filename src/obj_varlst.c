/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_varlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:08:01 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
 * t_done */
void	var_clean(t_lstvar *origin)
{
	t_myvar	*i;

	if (!origin)
		return ;
	i = *origin;
	while (i)
	{
		*origin = (*origin)->next;
		free(i->name);
		if (i->value)
			free(i->value);
		free(i);
		i = *origin;
	}
	*origin = NULL;
}

void	var_update(t_myvar *var, char *name, char *value)
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
	size_t	len;

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
int	var_pop(t_lstvar *origin, t_myvar *var)
{
	if (!var)
		return (-1);
	if (origin && *origin == var)
		*origin = var->next;
	if (var->prev)
		var->prev->next = var->next;
	if (var->next)
		var->next->prev = var->prev;
	var->next = NULL;
	var->prev = NULL;
	var_clean(&var);
	return (0);
}
