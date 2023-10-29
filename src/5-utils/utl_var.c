/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/29 12:53:58 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	split_name(char *str, char **split, char **name, int *append)
{
	char	*eq;

	*append = 0;
	*split = ft_strchr(str, '=');
	eq = ft_strchr(str, '+');
	if (eq && eq + 1 == *split)
		*append = 1;
	if (!*split)
		*split = str + ft_strlen(str);
	if (eq && eq + 1 == *split)
		*split = eq;
	*name = ft_substr(str, 0, *split - str);
	if (**split == '+')
		(*split)++;
	if (!name_check(*name))
		return (-1);
	return (0);
}

/*
 * ft_strchr is secured in case str == NULL
 * it SHOULD BE DEPENDING ON WHICH LIBFT
 * t_done */
int	var_parsing(t_lstvar *lst, char *str)
{
	char	*split;
	char	*name;
	char	*value;
	int		append;

	if (!lst || !str || !*str)
		return (-1);
	if (split_name(str, &split, &name, &append))
		return (-1);
	if (split[0] == '\0')
		value = NULL;
	else
	{
		value = ft_substr(str, split - str + 1, ft_strlen(split + 1));
		if (!value)
			return (free(name), -1);
	}
	if (append)
		value = ft_strjoin2(var_get_value(*lst, name), value, 0, 1);
	if (!var_add(lst, name, value))
		return (0);
	if (value)
		free(value);
	return (free(name), -1);
}

/*
 * t_done */
t_lstvar	var_get(t_lstvar lst, char *name)
{
	size_t	len;

	if (!name || !*name || !lst)
		return (NULL);
	len = ft_strlen(name);
	while (lst)
	{
		if (len == ft_strlen(lst->name) && !ft_strncmp(lst->name, name, len))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
 * if not found
 * of if unitialized : return NULL
 * * t_done */
char	*var_get_value(t_lstvar lst, char *name)
{
	t_myvar	*found;

	found = var_get(lst, name);
	if (!found)
		return (NULL);
	return (found->value);
}

/*
 * return a malloc'd char NAME=VALUE
 * NULL if error
 * t_done */
char	*var_get_string(t_myvar *var)
{
	char	*ret;
	char	*part;

	if (!var)
		return (NULL);
	part = ft_strjoin(var->name, "=");
	if (!part)
		return (NULL);
	ret = ft_strjoin(part, var->value);
	return (free(part), ret);
}
