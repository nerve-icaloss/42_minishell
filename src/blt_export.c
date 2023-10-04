/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:32:35 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:08:53 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "utils_var.h"

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
		if ((*s == '"' && ++s) || (*s == '\\' && ++s) || (++s && 0))
			count++;
	}
	ret = malloc(sizeof(char) * (count + 1));
	if (!ft_memset(ret, '\0', sizeof(char) * (count + 1)))
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
/*
 * export does check for numbers at first character of variable name
 * */
int	export_builtin(char **av, t_myenv *myenv)
{
	int	len;

	if (!av || !av[0] || !myenv)
		return (-1);
	if (!av[1])
		return (print_export(myenv));
	len = 1;
	while (av[len])
	{
		if (ft_isdigit(*av[len]))
			ft_dprintf(2, "export: '%s' : not a valid identifier\n", av[len]);
		else if (var_parsing(&myenv->lst_var, av[len]))
			return (-1);
		len++;
	}
	if (len > 1)
	{
		if (env_update_count(myenv) || envp_update(myenv))
			return (ft_dprintf(2, "WARN: minor error while updating envp\n"),
					0);
	}
	return (0);
}
