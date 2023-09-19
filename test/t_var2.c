/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:56:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/19 15:26:41 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "criterion/criterion.h"
#include "criterion/parameterized.h"
#include "criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

typedef struct s_exp {
	int r;
	char *s;
	t_myvar expected;
} t_exp;

typedef struct s_tpa {
	int r;
	char *s;
	t_lstvar expected;
} t_tpa;

void free_char_t(struct criterion_test_params *crp)
{
	t_tpa *strings = (t_tpa *) crp->params;
	for (size_t i = 0; i < crp->length; ++i) {
		cr_free(strings[i].expected->name);
		cr_free(strings[i].expected->value);
		cr_free(strings[i].expected);
		cr_free(strings[i].s);
		cr_free(strings[i].s);
	}
	cr_free(strings);
}

static char *cr_strdup(const char *str)
{
	if (!str)
		return (NULL);
	char *ptr = cr_malloc(sizeof(char) * strlen(str) + 1);
	if (ptr)
		strcpy(ptr, str);
	return ptr;
}

t_tpa exp_dup(t_exp *e)
{
	t_tpa ret;

	if (!e)
		return (ret);
	ret.s = cr_strdup(e->s);
	ret.r = e->r;
	ret.expected = cr_malloc(sizeof(t_lstvar));
	if (!ret.expected)
		return (ret);
	ret.expected->name = NULL;
	ret.expected->value = NULL;
	if (e->expected.name)
	{
		ret.expected->name = cr_strdup(e->expected.name);
	}
	if (e->expected.value)
		ret.expected->value = cr_strdup(e->expected.value);
	ret.expected->next = NULL;
	ret.expected->prev = NULL;
	return (ret);
}

ParameterizedTestParameters(var2, var_parsing_loop) {
	int len;
	t_exp	setting[] = {
		{
			0,
			"test=test",
			{
				"test",
				"test",
				NULL,
				NULL
			},
		},
		{
			0,
			"salut=test",
			{
				"salut",
				"test",
				NULL,
				NULL
			},
		},
		{
			-1,
			"",
			{
				"test",
				"test",
				NULL,
				NULL
			},
		},
		{
			0,
			"test=",
			{
				"test",
				"",
				NULL,
				NULL
			},
		},
		{
			0,
			"test",
			{
				"test",
				NULL,
				NULL,
				NULL
			},
		},
	};
	t_tpa	*strings;

	len = sizeof(setting) / sizeof(t_exp);
	strings = cr_malloc(sizeof (t_tpa) * len);
	for (size_t i = 0; i < len; i++)
	{
		strings[i] = exp_dup(setting + i);
	}
	return (cr_make_param_array(t_tpa, strings, len, free_char_t));
}

t_lstvar lstvar_res;

static void free_lstvar(void)
{
	if (lstvar_res)
		free(lstvar_res);
	lstvar_res = NULL;
}

static int lstvar_cmp(t_lstvar a, t_lstvar b)
{
	if (!a || !b)
		return (puts("no something"), 0);
	if (a->name && b->name)
		if (strcmp(a->name, b->name))
			return (0);
	else
		if (a->name != b->name)
			return (0);
	if (a->value && b->value)
		if (strcmp(a->value, b->value))
			return (0);
	else
		if (a->value != b->value)
			return (0);
	return (1);
}

ParameterizedTest(t_tpa *set, var2, var_parsing_loop, .fini = free_lstvar, .timeout = 1.)
{
	if (!set)
		cr_fatal("NO SET DEFINED");
	if (!set->expected)
	{
		cr_log_error("testing '%s', return'%d'", set->s, set->r);
		cr_fatal("NO EXPECTED");
	}
	lstvar_res = NULL;
	cr_expect(eq(int, var_parsing(&lstvar_res, set->s), set->r), "Unexpected error while varparsing");
	if (lstvar_res)
		cr_assert(lstvar_cmp(lstvar_res, set->expected));
}
