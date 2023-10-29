/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:32:35 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/29 16:53:11 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	name_check(char *s)
{
	size_t	len;
	char	*k;
	char	*eq;

	if (!s)
		return (0);
	k = ft_strchr(s, '=');
	eq = ft_strchr(s, '+');
	if (eq && eq + 1 == k)
		k = eq;
	if (k)
		len = k - s;
	else
		len = ft_strlen(s);
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	while (*s && len-- > 0 && (ft_isalnum(*s) || *s == '_'))
		s++;
	if (!*s || *s == '=' || (*s == '+' && *(s + 1) == '='))
		return (1);
	return (0);
}

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
	while (var && var->next)
		var = var->next;
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
		var = var->prev;
	}
	return (0);
}

size_t	get_value_size(char *s, t_myenv *env)
{
	char	*k;
	char	*eq;
	size_t	len;

	if (!s)
		return (0);
	k = ft_strchr(s, '=');
	eq = ft_strchr(s, '+');
	len = 0;
	if (k && *k)
		len = ft_strlen(k + 1);
	if (eq && k == eq + 1 && env)
	{
		*eq = '\0';
		len += ft_strlen(var_get_value(env->lst_var, s));
		*eq = '+';
	}
	return (len);
}

/*
 * export builtin
 * export does check for numbers at first character of variable name
 * */
int	export_builtin(char **av, t_myenv *env)
{
	int	len;
	int	ret;

	if (!av || !av[0] || !env)
		return (-1);
	if (!av[1])
		return (print_export(env));
	len = 1;
	ret = 0;
	while (av[len])
	{
		if (!name_check(av[len]) && ++ret)
			ft_dprintf(2, "minishell: export: `%s' : not a valid identifier\n",
				av[len]);
		else if (get_value_size(av[len], env) > 10000 && ++ret)
			ft_dprintf(2, "minishell: export: env var max_size reached\n");
		else if (var_parsing(&env->lst_var, av[len]))
			return (-1);
		len++;
	}
	if (env_update_count(env) || envp_update(env))
		return (ft_dprintf(2,
				"minishell: export: minor error while updating envp\n"), 0);
	return (ret > 0);
}
