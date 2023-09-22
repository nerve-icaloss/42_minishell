/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:56:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/20 15:38:58 by hmelica          ###   ########.fr       */
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
	if (e->s)
		ret.s = cr_strdup(e->s);
	else
		ret.s = NULL;
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

/*
 * set name to null if lst_var is supposed to be null
 * */
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
				NULL,
				NULL,
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
		cr_log_info("duplicating '%s'", setting[i].s);
		// TODO segfault with 'test='
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
	cr_expect(eq(int, var_parsing(&lstvar_res, set->s), set->r), "Unexpected error while varparsing with '%s'", set->s);
	cr_assert(set->expected != NULL, "test preparation error");
	if (lstvar_res)
	{
		if (!set->expected->name)
			cr_fatal("lst_var edited while mistaken");
		if (lstvar_res->name)
			cr_expect(eq(str, set->expected->name, lstvar_res->name), "name wrong");
		else
			cr_fatal("name unset");
		if (lstvar_res->value && set->expected->value)
			cr_expect(eq(str, set->expected->value, lstvar_res->value), "value wrong");
		else
			cr_expect(set->expected->value == NULL && lstvar_res->value == NULL, "value null error, got '%s' expected '%s', with '%s'", lstvar_res->value, set->expected->value, set->s);
	}
	else
		cr_assert(set->expected->name == NULL, "lst_var not edited with '%s'", set->s);
}
