/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:32:35 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 17:05:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

TEST_STATIC char	*format_export(char *s)
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

static int	print_export(t_myenv *env)
{
	t_lstvar	var;
	char		*s;

	var = env->lst_var;
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
int	export_builtin(char **av, t_myenv *env)
{
	int	len;

	if (!av || !av[0] || !env)
		return (-1);
	if (!av[1])
		return (print_export(env));
	len = 1;
	while (av[len])
	{
		if (ft_isdigit(*av[len]))
			ft_dprintf(2, "export: '%s' : not a valid identifier\n", av[len]);
		else if (var_parsing(&env->lst_var, av[len]))
			return (-1);
		len++;
	}
	if (len > 1)
	{
		if (env_update_count(env) || envp_update(env))
			return (ft_dprintf(2, "WARN: minor error while updating envp\n"),
				0);
	}
	return (0);
}
