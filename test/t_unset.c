/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:20:06 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/24 21:33:10 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "criterion/criterion.h"
#include "criterion/parameterized.h"
#include "criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

t_lstvar t;

void lstprint(t_lstvar i, char *a)
{
	while (i)
	{
		cr_log_info("#### %s '%s'='%s'", a, i->name, i->value);
		i = i->next;
	}
	cr_log_info("-----------------------------------------------------------");
}

void unset_init(void)
{
	t = NULL;

	var_parsing(&t, "q=q");
	var_parsing(&t, "p=p");
	var_parsing(&t, "o=o");
	var_parsing(&t, "notthere");
	var_parsing(&t, "n=n");
	var_parsing(&t, "m=m");
	var_parsing(&t, "l=l");
	var_parsing(&t, "k=k");
	var_parsing(&t, "hello=");
	var_parsing(&t, "j=j");
	var_parsing(&t, "i=i");
	var_parsing(&t, "h=h");
	var_parsing(&t, "g=g");
	var_parsing(&t, "f=f");
	var_parsing(&t, "e=e");
	var_parsing(&t, "d=d");
	var_parsing(&t, "c=c");
	var_parsing(&t, "b=b");
	var_parsing(&t, "a=a");
	var_parsing(&t, "coucou=jesuisheureux");
}

void unset_clean(void)
{
	if (t)
		var_clean(&t);
}

Test(unset, builtin, .description="Testing unset builtin", .init=unset_init, .fini=unset_clean)
{
	char *a[] = {NULL};
	char *aa[] = {"filepath", NULL};
	char *b[] = {"filepath", "a", "c", "e", NULL};
	char *c[] = {"filepath", "c", "b", NULL};
	char *d[] = {"filepath", "hello", "notthere", NULL};
	char *e[] = {"filepath", "coucou", NULL};
	t_lstvar i;

	cr_assert(ne(ptr, t, NULL), "init failed");
	cr_assert(eq(int, -1, unset_builtin(NULL, &t)), "Doesnt fail when no arg");
	cr_assert(eq(int, -1, unset_builtin(c, NULL)), "Doesnt fail when no *lst");
	// a
	i = t;
	cr_assert(eq(int, -1, unset_builtin(a, &t)), "doesnt fail with a");
	cr_assert(eq(ptr, i, t), "lst edited with empty arg");
	cr_assert(eq(int, 0, unset_builtin(aa, &t)), "fail with aa");
	cr_assert(eq(ptr, i, t), "lst edited with no arg");
	// b
	i = t->next;
	cr_assert(eq(int, 0, unset_builtin(b, &t)), "fail with b");
	cr_assert(ne(ptr, i, t), "lst->next not updated");
	// c
	i = t->next;
	cr_assert(eq(int, 0, unset_builtin(c, &t)), "fail with c");
	cr_assert(ne(ptr, i, t->next), "lst->next not updated with unset var");
	// d
	cr_assert(ne(ptr, NULL, var_get(t, "hello")), "hello not found");
	cr_assert(ne(ptr, NULL, var_get(t, "notthere")), "notthere not found");
	cr_assert(eq(int, 0, unset_builtin(d, &t)), "fail with d");
	cr_assert(eq(ptr, NULL, var_get(t, "notthere")), "notthere found");
	cr_assert(eq(ptr, NULL, var_get(t, "hello")), "hello found");
	// e
	i = t->next;
	cr_assert(eq(int, 0, unset_builtin(e, &t)), "fail with e");
	cr_assert(eq(ptr, i, t), "t not updated when first is poped");
}
