/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:57:42 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 11:47:52 by hmelica          ###   ########.fr       */
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

int	var_parsing(t_lstvar *lst, char *str)
{
	char	*split;
	char	*name;
	char	*value;
	int		len;

	if (!str || !lst)
		return (-1);
	split = ft_strchr(str, '=');
	if (!split)
		return (-1);
	name = malloc(sizeof(char) * (split - str + 1));
	if (!name)
		return (-1);
	ft_strlcpy(name, str, (split - str + 1));
	if (split[1] == '\0')
		value = NULL;
	else
	{
		len = ft_strlen(split + 1);
		value = malloc(sizeof(char) * (len + 1));
		if (!value)
			return (free(name), -1);
		ft_strlcpy(value, split + 1, len + 1);
	}
	return (var_add(lst, name, value));
}
