/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_offset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:46:50 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/25 20:12:28 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./universal.h"
#include "../criterion/include/criterion/criterion.h"
#include "../criterion/include/criterion/parameterized.h"
#include "../criterion/include/criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

char *cr_strdup(const char *str);

typedef struct s_doublestrint {
	size_t	offset;
	char	*in;
	char	*out;
}	t_doublestrint;

void free_doublestrint(struct criterion_test_params *crp) {
	t_doublestrint *strings = (t_doublestrint *) crp->params;
	for (size_t i = 0; i < crp->length; i++)
	{
		if (strings[i].in)
			cr_free(strings[i].in);
		if (strings[i].out)
			cr_free(strings[i].out);
	}
	cr_free(strings);
}

ParameterizedTestParameters(libft, offset) {
	int len;
	t_doublestrint	setting[] = {
		{
			0,
			NULL,
			NULL,
		},
		{
			2,
			NULL,
			NULL,
		},
		{
			0,
			"coucou je suis heureux",
			"coucou je suis heureux",
		},
		{
			7,
			"coucou je suis heureux",
			"je suis heureux",
		},
		{
			42,
			"coucou je suis heureux",
			"",
		},
	};
	t_doublestrint *strings;

	cr_log_info("Counting tests for libft offset");
	len = sizeof(setting) / sizeof(t_doublestrint);
	cr_log_info("Generating %d tests for libft offset", len);
	strings = cr_malloc(sizeof(setting));
	for (size_t i = 0; i < len; i++)
	{
		strings[i].offset = setting[i].offset;
		strings[i].in = NULL;
		strings[i].out = NULL;
		if (setting[i].in)
			strings[i].in = cr_strdup(setting[i].in);
		if (setting[i].out)
			strings[i].out = cr_strdup(setting[i].out);
	}
	cr_log_info("Tests generated for libft offset");
	return (cr_make_param_array(t_doublestrint, strings, len, free_doublestrint));
}

ParameterizedTest(t_doublestrint *set, libft, offset, .timeout = 2.)
{
	ft_offset(set->in, set->offset);
	if (set->out && set->in)
		cr_assert(eq(str, set->in, set->out));
	else
		cr_assert(eq(ptr, set->in, set->out));
}
