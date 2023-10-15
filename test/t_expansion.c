/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:57:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/15 14:42:35 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "include/criterion/criterion.h"
#include "include/criterion/parameterized.h"
#include "include/criterion/new/assert.h"
#include <string.h>

// test var expansion there
char *cr_strdup(const char *str);

typedef struct s_doublestr {
	char	*in;
	char	*out;
}	t_doublestr;

void free_doublestr(struct criterion_test_params *crp) {
	t_doublestr *strings = (t_doublestr *) crp->params;
	for (size_t i = 0; i < crp->length; i++)
	{
		if (strings[i].in)
			cr_free(strings[i].in);
		if (strings[i].out)
			cr_free(strings[i].out);
	}
	cr_free(strings);
}

ParameterizedTestParameters(expansion, var_expansion) {
	int len;
	t_doublestr	setting[] = {
		{
			NULL,
			NULL,
		},
		{
			"coucou je suis heureux $ $ $ ",
			"coucou je suis heureux $ $ $ ",
		},
		{
			"$mood",
			"coucou je suis heureux",
		},
		{
			"$non",
			"",
		},
		{
			"$ je suis fun $a $",
			"$ je suis fun aaa $",
		},
		{
			"$a$b$c",
			"aaabbbccc",
		},
	};
	t_doublestr *strings;

	cr_log_info("Counting tests for var_expansion");
	len = sizeof(setting) / sizeof(t_doublestr);
	cr_log_info("Generating %d tests for var_expansion", len);
	strings = cr_malloc(sizeof(setting));
	for (size_t i = 0; i < len; i++)
	{
		strings[i].in = NULL;
		strings[i].out = NULL;
		if (setting[i].in)
			strings[i].in = cr_strdup(setting[i].in);
		if (setting[i].out)
			strings[i].out = cr_strdup(setting[i].out);
	}
	cr_log_info("Tests generated for var_expansion");
	return (cr_make_param_array(t_doublestr, strings, len, free_doublestr));
}

ParameterizedTest(t_doublestr *set, expansion, var_expansion, .timeout = 2.)
{
	t_myenv env;
	char *s;

	if (!set)
		cr_fatal("No arg");
	env.lst_var = NULL;
	var_parsing(&env.lst_var, "mood=coucou je suis heureux");
	var_parsing(&env.lst_var, "a=aaa");
	var_parsing(&env.lst_var, "b=bbb");
	var_parsing(&env.lst_var, "c=ccc");
	s = NULL;
	if (set->in)
		s = ft_strdup(set->in);
	var_expansion(&s, &env);
	if (s == NULL)
		cr_expect(eq(ptr, s, set->out), "str not unset when supposed to");
	else
	{
		cr_expect(eq(str, s, set->out), "str does not match");
		free(s);
	}
	var_clean(&env.lst_var);
}
