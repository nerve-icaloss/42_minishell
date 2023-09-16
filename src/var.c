/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:57:42 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 10:46:36 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
 * ft_strchr is secured in case str == NULL
 * it SHOULD BE DEPENDING ON WHICH LIBFT
 * */
int	var_parsing(t_lstvar *lst, char *str)
{
	char	*split;
	char	*name;
	char	*value;

	split = ft_strchr(str, '=');
	if (!split || !lst)
		return (-1);
	name = ft_substr(str, 0, split - str);
	if (!name)
		return (-1);
	if (split[1] == '\0')
		value = NULL;
	else
	{
		value = ft_substr(str, split - str + 1, ft_strlen(split + 1));
		if (!value)
			return (free(name), -1);
	}
	if (var_add(lst, name, value))
	{
		if (value)
			free(value);
		return (free(name), -1);
	}
	return (0);
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

/*
 * return a malloc'd char NAME=VALUE
 * NULL if error
 * */
char	*var_get_string(t_lstvar var)
{
	char	*ret;
	char	*part;

	part = ft_strjoin(var->name, "=");
	if (!part)
		return (NULL);
	ret = ft_strjoin(part, var->value);
	return (free(part), ret);
}
