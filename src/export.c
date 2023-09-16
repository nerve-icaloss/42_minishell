/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:32:35 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 22:34:57 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*format_export(char *s)
{
	char	*ret;
	char	*origin;
	int		count;

	if (!s)
		return (NULL);
	origin = s;
	count = ft_strlen(s);
	while (*s)
	{
		if (*s == '"' || *s == '\\')
			count++;
		s++;
	}
	ret = malloc(sizeof(char) * (count + 1));
	ft_bzero(ret, sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	s = origin;
	origin = ret;
	while (*s && origin - ret < count + 1)
	{
		if (*s == '"' || *s == '\\')
			*(origin++) = '\\';
		*(origin++) = *(s++);
	}
	return (ret);
}

int	print_export(t_myenv *myenv)
{
	t_lstvar	var;
	char		*s;

	var = myenv->lst_var;
	while (var)
	{
		if (var->value)
		{
			s = format_export(var->value);
			printf("export %s=\"%s\"\n", var->name, s);
			free(s);
		}
		else
			printf("export %s\n", var->name);
		var = var->next;
	}
	return (0);
}

/*
 * export builtin
 * */
int	export(char **av, t_myenv *myenv)
{
	if (!av || !av[0] || !myenv)
		return (-1);
	if (!av[1])
		return (print_export(myenv));
	return (0);
}
