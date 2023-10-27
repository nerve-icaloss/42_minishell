/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:36:17 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/27 17:04:13 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	name_check(char *s)
{
	size_t	len;
	char	*k;

	if (!s)
		return (0);
	k = ft_strchr(s, '=');
	if (k)
		len = k - s;
	else
		len = ft_strlen(s);
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	while (*s && len-- > 0 && (ft_isalnum(*s) || *s == '_'))
		s++;
	if (!*s || *s == '=')
		return (1);
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

	if (!lst || !str || !*str)
		return (-1);
	split = ft_strchr(str, '=');
	if (!split)
		split = str + ft_strlen(str);
	name = ft_substr(str, 0, split - str);
	if (!name_check(name))
		return (-1);
	if (split[0] == '\0')
		value = NULL;
	else
	{
		value = ft_substr(str, split - str + 1, ft_strlen(split + 1));
		if (!value)
			return (free(name), -1);
	}
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
