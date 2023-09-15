/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:10:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 18:22:46 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include <stdio.h>

Test(var, cleaning, .description="Test of var_cleaning") {
	t_lstvar lst;

	lst = malloc(sizeof(t_myvar));
	cr_assert(lst != NULL, "Malloc error");
	lst->value = malloc(sizeof(char) * 7);
	cr_assert(lst->value != NULL, "Malloc error");
	lst->name = malloc(sizeof(char) * 7);
	cr_assert(lst->name != NULL, "Malloc error");
	var_clean(&lst);
	cr_expect(lst == NULL);
}

Test(var, var_parsing, .description="Test of var_parsing and var_add") {
	t_lstvar lst;

	lst = NULL;
	cr_assert(var_add(&lst, "coucou", "eh coucou") == 0, "var_add failed when tested");
	cr_assert(lst != NULL, "lst is not updated");
	cr_assert(eq(str, lst->name, "coucou"), "Wrong name when set manually");
	cr_assert(eq(str, lst->value, "eh coucou"), "Wrong value when set manually");
	cr_assert(lst->next == NULL, "Next is left unset");
	cr_assert(lst->prev == NULL, "Prev is left unset");
}

