/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:51:56 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/04 15:51:57 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../criterion/include/criterion/criterion.h"
#include "../criterion/include/criterion/parameterized.h"
#include "../criterion/include/criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

char *cr_strdup(const char *str);

static size_t	ft_sublen(const char *s, size_t len)
{
	size_t	size;

	size = 0;
	while (*s && len)
	{
		size++;
		s++;
		len--;
	}
	return (size);
}

static char	*cr_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	subsize;
	int		i;

	if (!s)
		return (NULL);
	if (strlen(s) < start)
		return (cr_calloc(sizeof(char), 1));
	s = s + start;
	subsize = ft_sublen(s, len);
	ret = cr_malloc(sizeof(*ret) * (subsize + 1));
	if (!ret)
		return (NULL);
	ret[subsize] = '\0';
	i = 0;
	while (s[i] && len)
	{
		ret[i] = s[i];
		i++;
		len--;
	}
	return (ret);
}

static int	cr_var_add(t_lstvar *origin, char *name, char *value)
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
		to_add = cr_malloc(sizeof(t_myvar));
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

static int	cr_var_parsing(t_lstvar *lst, char *str)
{
	char	*split;
	char	*name;
	char	*value;

	if (!lst || !str || !*str)
		return (-1);
	split = ft_strchr(str, '=');
	if (!split)
		split = str + ft_strlen(str);
	name = cr_substr(str, 0, split - str);
	if (!name)
		return (-1);
	if (split[0] == '\0')
		value = NULL;
	else
	{
		value = cr_substr(str, split - str + 1, ft_strlen(split + 1));
		if (!value)
			return (cr_free(name), -1);
	}
	if (!cr_var_add(lst, name, value))
		return (0);
	if (value)
		cr_free(value);
	return (cr_free(name), -1);
}

static int	cr_env_init(t_myenv *env, char **envp)
{
	if (!envp || !env)
		return (-1);
	env->lst_var = NULL;
	env->envp = NULL;
	while (*envp)
	{
		if (cr_var_parsing(&env->lst_var, *envp))
			return (var_clean(&env->lst_var), -1);
		envp++;
	}
	env->pwd = var_get(env->lst_var, "PWD");
	env->oldpwd = var_get(env->lst_var, "OLDPWD");
	env->home = var_get(env->lst_var, "HOME");
	env->shlvl = var_get(env->lst_var, "SHLVL");
	env->path = var_get(env->lst_var, "PATH");
	return (0);
}

// tab is argv after first NULL and envp before
typedef struct s_arg_test {
	t_myenv	env;
	int		ret_code;
	char	*expected;
	char	*tab[128]; // cette valeur est arbitraire
} t_arg_test;

typedef struct s_arg_t {
	t_myenv	env;
	int		ret_code;
	char	*expected;
	char	**tab;
} t_arg_t;

static void	cr_var_clean(t_lstvar *origin)
{
	t_myvar	*i;

	if (!origin)
		return ;
	i = *origin;
	while (i)
	{
		*origin = (*origin)->next;
		cr_free(i->name);
		if (i->value)
			cr_free(i->value);
		cr_free(i);
		i = *origin;
	}
	*origin = NULL;
}

void	free_arg(struct criterion_test_params *crp)
{
	t_arg_t *c;
	char **t;

	c = crp->params;
	for (size_t i = 0; i < crp->length; ++i)
	{
		if (c)
		{
			cr_var_clean(&c->env.lst_var);
			t = c->tab;
			while (*t)
				cr_free(*(t++));
			if (c->tab)
				cr_free(c->tab);
			if (c->expected)
				cr_free(c->expected);
		}
		c++;
	}
	cr_free((t_arg_t *)crp->params);
}

ParameterizedTestParameters(cd, arg_parser) {
	t_arg_test setting[] = {
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			0,
			"/", // - with normal OLDPWD
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"with normal OLDPWD",
				"-",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			1,
			"preset_str", // - with unset OLDPWD
			{
				"HOME=/usr",
				"PWD=/tmp",
				"VAR=value",
				NULL,
				"with unset OLDPWD",
				"-",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			1,
			"preset_str", // - with empty OLDPWD
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD",
				"VAR=value",
				NULL,
				"with empty OLDPWD",
				"-",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			0,
			"/usr", // with no arg
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"with no arg",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			1,
			"preset_str", // with no arg but home unset
			{
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"with no arg but home unset",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			1,
			"preset_str", // with no arg but no home
			{
				"HOME",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"with no arg but no home",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			-1,
			"preset_str", // with an error
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			0,
			"/dev", // /dev
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"/dev normal arg",
				"/dev",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			0,
			"--", // will raise an error later but shouldnt return oldpwd
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"will raise an error later but shouldnt return oldpwd",
				"--",
				NULL
			},
		},
		{
			{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}, // should stay init like this
			1,
			"preset_str", // to many arguments
			{
				"HOME=/usr",
				"PWD=/tmp",
				"OLDPWD=/",
				"VAR=value",
				NULL,
				"to many arguments",
				"-",
				"Coucou je suis heureux",
				NULL
			},
		},
	};

	char		**tab;
	t_arg_t		*ret;
	t_arg_t		*e;
	int			len;
	int			i;
	int			j;

	int count = sizeof(setting) / sizeof(t_arg_test);
	ret = cr_malloc(sizeof(t_arg_t) * count);
	e = ret;
	while (e - ret < count)
	{
		tab = setting[e - ret].tab;
		e->ret_code = setting[e - ret].ret_code;
		e->env = setting[e - ret].env;
		if (setting[e - ret].expected)
			e->expected = cr_strdup(setting[e - ret].expected);
		cr_env_init(&e->env, tab);
		i = 0;
		j = 0;
		while (tab[j++])
			; // decalage apres le premier null
		while (tab[j + i])
			i++;
		len = i + 1;
		e->tab = NULL;
		if (len)
		{
			e->tab = cr_malloc(len * sizeof(char *));
			i = 0;// dupliquer les arg ici
			while (i < len - 1)
			{
				e->tab[i] = cr_strdup(tab[i + j]);
				i++;
			}
			e->tab[i] = NULL;
		}
		e++;
	}
	cr_log_info("%d tests on cd arg parsing", count);
	return (cr_make_param_array(t_arg_t, ret, count, free_arg));
}

int	path_arg_parser(char **argv, t_myenv *myenv, char **path);

ParameterizedTest(t_arg_t *arg, cd, arg_parser, .timeout = 1)
{
	char *str = "preset_str";
	if (!arg)
		cr_fatal("no arg");
	cr_expect(eq(int, path_arg_parser(arg->tab, &arg->env, &str), arg->ret_code),
			"return code wrong\n%s", *arg->tab);
	cr_expect(eq(str, str, arg->expected), "Expected return path wrong\n%s", *arg->tab);
}

Test(cd, builtin)
{
	cr_log_warn("cd builtin not tested, tests needs to be done manually");
}
