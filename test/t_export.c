/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:57:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/22 15:01:07 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "criterion/criterion.h"
#include "criterion/parameterized.h"
#include "criterion/new/assert.h"
#include <string.h>

char	*format_export(char *s);

typedef struct s_set {
	char *s;
	char *expected;
} t_set;


char *result;

void free_result(void)
{
	if (result)
		free(result);
}

void free_set(struct criterion_test_params *crp)
{
	t_set *c;

	c = crp->params;
	for (size_t i = 0; i < crp->length; ++i)
	{
		if (c)
		{
			if (c->s)
				cr_free(c->s);
			if (c->expected)
				cr_free(c->expected);
		}
		c++;
	}
	cr_free((t_set *)crp->params);
}

char *cr_strdup(const char *str)
{
	if (!str)
		return (NULL);
	char *ptr = cr_malloc(strlen(str) + 1);
	if (ptr)
		strcpy(ptr, str);
	return ptr;
}

ParameterizedTestParameters(export, format)
{
	t_set	setting[] = {
		{NULL, NULL},
		{"", ""},
		{"coucou", "coucou"},
		// there repeat
		{"\\", "\\\\"},
		{"\\\\", "\\\\\\\\"},
		{"\"", "\\\""},
		{"\"\"", "\\\"\\\""},
		// there repeat
		{"\\coucou", "\\\\coucou"},
		{"\\\\coucou", "\\\\\\\\coucou"},
		{"\"coucou", "\\\"coucou"},
		{"\"\"coucou", "\\\"\\\"coucou"},
		// there repeat
		{"coucou\\", "coucou\\\\"},
		{"coucou\\\\", "coucou\\\\\\\\"},
		{"coucou\"", "coucou\\\""},
		{"coucou\"\"", "coucou\\\"\\\""},
		// there repeat
		{"coucou\\coucou", "coucou\\\\coucou"},
		{"coucou\\\\coucou", "coucou\\\\\\\\coucou"},
		{"coucou\"coucou", "coucou\\\"coucou"},
		{"coucou\"\"coucou", "coucou\\\"\\\"coucou"},
		// there repeat
		{"coucou\\coucou\\coucou", "coucou\\\\coucou\\\\coucou"},
		{"coucou\"coucou\"coucou", "coucou\\\"coucou\\\"coucou"},
	};
	t_set	*params;
	t_set	*i;
	int		count;

	count = sizeof(setting) / sizeof(t_set);
	params = cr_malloc(count * sizeof(t_set));
	i = params;
	while (i - params < count)
	{
		if (setting[i - params].s)
			i->s = cr_strdup(setting[i - params].s);
		else
			i->s = NULL;
		if (setting[i - params].expected)
			i->expected = cr_strdup(setting[i - params].expected);
		else
			i->expected = NULL;
		i++;
	}
	cr_log_info("%d tests on format export", count);
	return (cr_make_param_array(t_set, params, count, free_set));
}

ParameterizedTest(t_set *set, export, format, .fini = free_result, .timeout = 1.)
{
	result = NULL;
	result = format_export(set->s);
	if (set->expected == NULL)
		cr_assert(result == NULL, "format is set while not expected");
	else if (result != NULL)
		cr_assert(eq(str, result, set->expected), "Wrong format");
	else
		cr_fatal("format_export failed with '%s' (expected '%s' got '%s')", set->s, set->expected, result);
}
