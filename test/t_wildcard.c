/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_wildcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:51:56 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 21:48:59 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./universal.h"
#include "../criterion/include/criterion/criterion.h"
#include "../criterion/include/criterion/parameterized.h"
#include "../criterion/include/criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

char *cr_strdup(const char *str);

typedef struct s_arg_wc {
	int		ret; // expected return code
	char	*s;
	char	*close;
	char	*path;
}	t_arg_wc;

void	free_wc_arg(struct criterion_test_params *crp)
{
	t_arg_wc *c;

	c = crp->params;
	for (size_t i = 0; i < crp->length; ++i)
	{
		if (c)
		{
			if (c->s)
				cr_free(c->s);
			if (c->close)
				cr_free(c->close);
			if (c->path)
				cr_free(c->path);
		}
		c++;
	}
	cr_free((t_arg_wc *)crp->params);
}

ParameterizedTestParameters(wildcard, prev) {
	t_arg_wc setting[] = {
		{
			0,
			"coucou/hello*trop/super",
			"hello",
			"coucou/"
		},
		{
			0,
			"*",
			"",
			"./"
		},
		{
			0,
			"coucou/*trop/super",
			"",
			"coucou/"
		},
		{
			0,
			"coucou/nice/hello*trop/super",
			"hello",
			"coucou/nice/"
		},
	};

	t_arg_wc	*ret;
	int			len;
	int			i;

	int count = sizeof(setting) / sizeof(t_arg_wc);
	ret = cr_malloc(sizeof(t_arg_wc) * count);
	i = 0;
	while (i < count)
	{
		bzero(ret + i, sizeof(t_arg_wc));
		ret[i].ret = setting[i].ret;
		if (setting[i].s)
			ret[i].s = cr_strdup(setting[i].s);
		if (setting[i].close)
			ret[i].close = cr_strdup(setting[i].close);
		if (setting[i].path)
			ret[i].path = cr_strdup(setting[i].path);
		i++;
	}
	cr_log_info("%d tests on wildcard prev", count);
	return (cr_make_param_array(t_arg_wc, ret, count, free_wc_arg));
}

int	wc_init_prev(t_wildcard *wc, char *s);
int	wc_init_next(t_wildcard *wc);

ParameterizedTest(t_arg_wc *arg, wildcard, prev, .timeout = 2)
{
	t_wildcard wc;

	wc.s = strdup(arg->s);
	wc.wc = ft_strchr(wc.s, '*');
	cr_expect(eq(int, wc_init_prev(&wc, wc.s), arg->ret));
	if (arg->path && wc.path)
		cr_expect(eq(str, arg->path, wc.path));
	else
	{
		if (wc.path)
			cr_expect(eq(ptr, arg->path, wc.path), "%s", wc.path);
		else
			cr_expect(eq(ptr, arg->path, wc.path));
	}
	if (arg->close && wc.glob_prev)
		cr_expect(eq(str, arg->close, wc.glob_prev));
	else
	{
		if (wc.glob_prev)
			cr_expect(eq(ptr, arg->close, wc.glob_prev), "%s", wc.glob_prev);
		else
			cr_expect(eq(ptr, arg->close, wc.glob_prev));
	}
	if (wc.s)
		free(wc.s);
	if (wc.path)
		free(wc.path);
	if (wc.glob_prev)
		free(wc.glob_prev);
}

ParameterizedTestParameters(wildcard, next) {
	t_arg_wc setting[] = {
		{
			0,
			"coucou/hello*trop/super",
			"trop",
			"/super"
		},
		{
			0,
			"*",
			"",
			""
		},
		{
			0,
			"coucou/genial*/super",
			"",
			"/super"
		},
		{
			0,
			"coucou/hello*trop/super/metropbien",
			"trop",
			"/super/metropbien"
		},
		{
			0,
			"coucou/hello*.c",
			".c",
			""
		},
	};

	t_arg_wc	*ret;
	int			len;
	int			i;

	int count = sizeof(setting) / sizeof(t_arg_wc);
	ret = cr_malloc(sizeof(t_arg_wc) * count);
	i = 0;
	while (i < count)
	{
		bzero(ret + i, sizeof(t_arg_wc));
		ret[i].ret = setting[i].ret;
		if (setting[i].s)
			ret[i].s = cr_strdup(setting[i].s);
		if (setting[i].close)
			ret[i].close = cr_strdup(setting[i].close);
		if (setting[i].path)
			ret[i].path = cr_strdup(setting[i].path);
		i++;
	}
	cr_log_info("%d tests on wildcard prev", count);
	return (cr_make_param_array(t_arg_wc, ret, count, free_wc_arg));
}

ParameterizedTest(t_arg_wc *arg, wildcard, next, .timeout = 2)
{
	t_wildcard wc;

	wc.following = NULL;
	wc.glob_next = NULL;
	wc.s = strdup(arg->s);
	wc.wc = ft_strchr(wc.s, '*');
	cr_expect(eq(int, wc_init_next(&wc), arg->ret));
	if (arg->path && wc.following)
		cr_expect(eq(str, arg->path, wc.following));
	else
	{
		if (wc.following)
			cr_expect(eq(ptr, arg->path, wc.following), "%s", wc.following);
		else
			cr_expect(eq(ptr, arg->path, wc.following));
	}
	if (arg->close && wc.glob_next)
		cr_expect(eq(str, arg->close, wc.glob_next));
	else
	{
		if (wc.glob_next)
			cr_expect(eq(ptr, arg->close, wc.glob_next), "%s", wc.glob_next);
		else
			cr_expect(eq(ptr, arg->close, wc.glob_next));
	}
	if (wc.s)
		free(wc.s);
	if (wc.following)
		free(wc.following);
	if (wc.glob_next)
		free(wc.glob_next);
}

ParameterizedTestParameters(wildcard, glob_name) {
	t_arg_wc setting[] = {
		{
			0,
			"wildcard.c",
			"w",
			"d"
		},
		{
			1,
			"blt_export.c",
			"",
			".c"
		},
		{
			1,
			"wildcard.c",
			"w",
			"c"
		},
		{
			1,
			"coucou je suis heureux",
			"coucou",
			" je * heureux"
		},
		{
			1,
			"wildcard.c",
			"w",
			"card.*"
		},
		{
			1,
			"wildcard.c",
			"",
			"c"
		},
		{
			1,
			"wildcard.c",
			"w",
			""
		},
		{
			1,
			"coucou je suis heureux",
			"coucou",
			" * * *"
		},
		{
			1,
			"coucouhehe je suis heureux",
			"coucou",
			" * * *"
		},
		{
			0,
			"coucou je suis heureux",
			"coucou",
			" je* triste"
		},
		{
			1,
			"coucou je suis heureux",
			"",
			"*"
		},
		{
			1,
			"coucou je suis heureux",
			"",
			""
		},
		{
			0,
			"coucou je suis heureux",
			"coucou",
			"*  *"
		},
		{
			0,
			"toto",
			"t",
			""
		},
		{
			0,
			"titi",
			""
			"t",
		},
		{
			0,
			"tata",
			"",
			"t"
		},
		{
			t,
			"test",
			"",
			"t"
		},

	};

	t_arg_wc	*ret;
	int			len;
	int			i;

	int count = sizeof(setting) / sizeof(t_arg_wc);
	ret = cr_malloc(sizeof(t_arg_wc) * count);
	i = 0;
	while (i < count)
	{
		bzero(ret + i, sizeof(t_arg_wc));
		ret[i].ret = setting[i].ret;
		if (setting[i].s)
			ret[i].s = cr_strdup(setting[i].s);
		if (setting[i].close)
			ret[i].close = cr_strdup(setting[i].close);
		if (setting[i].path)
			ret[i].path = cr_strdup(setting[i].path);
		i++;
	}
	cr_log_info("%d tests on wildcard glob_name", count);
	return (cr_make_param_array(t_arg_wc, ret, count, free_wc_arg));
}

ParameterizedTest(t_arg_wc *arg, wildcard, glob_name, .timeout = 2)
{
	cr_expect(eq(int, glob_name(arg->s, arg->close, arg->path), arg->ret),
			"(%s)%s(%s)", arg->close, arg->s, arg->path);
}
