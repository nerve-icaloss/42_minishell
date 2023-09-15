/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:57:42 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 14:38:17 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	var_parsing(t_lstvar *lst, char *str)
{
	char	*split;
	char	*name;
	char	*value;

	if (!str || !lst)
		return (-1);
	split = ft_strchr(str, '=');
	if (!split)
		return (-1);
	name = ft_substr(str, 0, split - str);
	if (!name)
		return (-1);
	if (split[1] == '\0')
		value = NULL;
	else
	{
		value = ft_substr(str, split - str, ft_strlen(split + 1));
		if (!value)
			return (free(name), -1);
	}
	return (var_add(lst, name, value));
}

t_lstvar	var_get(t_lstvar lst, char *name)
{
	int	len;

	if (!name || !lst)
		return (NULL);
	len = ft_strlen(name);
	while (lst)
	{
		if (!ft_strncmp(lst->name, name, len))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
 * if not found : return NULL
 * if unitialized : return const "\0"
 * */
char	*var_get_value(t_lstvar lst, char *name)
{
	t_lstvar	found;

	found = var_get(lst, name);
	if (!found)
		return (NULL);
	if (found->value == NULL)
		return ("");
	return (found->value);
}
