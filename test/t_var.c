/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:10:09 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:28:27 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "criterion/criterion.h"
#include "criterion/parameterized.h"
#include "criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

t_lstvar lst;

void clean_lst(void)
{
	var_clean(&lst);
}

Test(var, cleaning, .description="Test of var_cleaning") {
	lst = NULL;
	var_clean(NULL);
	var_clean(&lst);
	lst = malloc(sizeof(t_myvar));
	lst->next = NULL;
	lst->prev = NULL;
	cr_assert(lst != NULL, "Malloc error");
	lst->value = malloc(sizeof(char) * 7);
	cr_assert(lst->value != NULL, "Malloc error");
	lst->name = malloc(sizeof(char) * 7);
	cr_assert(lst->name != NULL, "Malloc error");
	var_clean(&lst);
	cr_expect(lst == NULL);
}

Test(var, var_add, .description="Test of var_add", .fini = clean_lst) {
	t_lstvar i;
	char *a, *b;

	lst = NULL;
	cr_assert(var_add(&lst, NULL, NULL) != 0, "adding when no name");
	a = strdup("coucou");
	b = strdup("eh coucou");
	cr_assert(var_add(NULL, a, b) != 0, "add when no list ??");
	// unexpected input
	// adding a value
	a = strdup("coucou");
	b = strdup("eh coucou");
	cr_assert(var_add(&lst, a, b) == 0, "failed when tested");
	cr_assert(lst != NULL, "lst is not updated");
	cr_assert(eq(str, lst->name, "coucou"), "Wrong name when set manually");
	cr_assert(eq(str, lst->value, "eh coucou"), "Wrong value when set manually");
	cr_assert(lst->next == NULL, "Next is left unset");
	cr_assert(lst->prev == NULL, "Prev is left unset");
	i = lst;
	// adding another value
	a = strdup("salut");
	b = strdup("eh salut");
	cr_assert(var_add(&lst, a, b) == 0, "failed when tested");
	cr_assert(lst != NULL, "lst is not updated");
	cr_assert(eq(str, lst->name, "salut"), "Wrong name when set manually");
	cr_assert(eq(str, lst->value, "eh salut"), "Wrong value when set manually");
	cr_assert(lst->next == i, "Next is not updated");
	cr_assert(lst->prev == NULL, "Prev is left unset");
	cr_assert(i->prev == lst, "Prev is not updated on next");
	var_clean(&lst);
	cr_assert(lst == NULL, "Cleaning while testing not working");
	// adding a var with no value
	a = strdup("name_is_name");
	cr_assert(var_add(&lst, a, NULL) == 0, "Fail");
	cr_assert(lst != NULL, "lst is not updated");
	cr_assert(eq(str, lst->name, "name_is_name"), "Wrong name when set manually");
	cr_assert(lst->value == NULL, "Wrong value when unset");
	cr_assert(lst->next == NULL, "Next is left unset");
	cr_assert(lst->prev == NULL, "Prev is left unset");
	var_clean(&lst);
	// adding duplicate name
	a = strdup("name");
	b = strdup("eh coucou");
	cr_assert(var_add(&lst, a, b) == 0, "Fail");
	cr_assert(lst != NULL, "lst not updated");
	cr_assert(eq(str, lst->name, "name"), "Wrong value when unset");
	cr_assert(eq(str, lst->value, "eh coucou"), "Wrong value when unset");
	a = strdup("name");
	b = strdup("je suis heureux");
	cr_assert(var_add(&lst, a, b) == 0, "Fail");
	cr_assert(lst->next == NULL, "Another var added");
	cr_assert(lst->prev == NULL, "Another var added but nonsens");
	cr_assert(eq(str, lst->name, "name"), "Wrong value when unset");
	cr_assert(ne(str, lst->value, "eh coucou"), "Wrong value when unset");
	cr_assert(eq(str, lst->value, "je suis heureux"), "Wrong value when unset");
}

/*
Test(var, var_parsing, .description="Test of var_parsing", .fini = clean_lst)
{
	lst = NULL;
	// unexpected situations
	cr_log_info("Testing falses situations");
	cr_assert(var_parsing(NULL, "non") != 0, "no lst doesn't fail");
	cr_assert(var_parsing(&lst, NULL) != 0, "no str doesn't fail");
	cr_assert(var_parsing(NULL, NULL) != 0, "no str nor lst doesn't fail");
	cr_assert(var_parsing(&lst, "thereisno_equal") != 0, "no = doesn't fail");
	// expected behavior
	cr_log_info("Testing normal situations");
	cr_assert(var_parsing(&lst, "var=coucou") == 0, "failed when tested");
	cr_assert(lst != NULL, "lst left unset");
	cr_assert(lst->name != NULL, "name left unset");
	cr_assert(lst->value != NULL, "value left unset");
	cr_assert(eq(str, lst->name, "var"), "name set wrong");
	cr_assert(eq(str, lst->value, "coucou"), "value set wrong");
	// no value
	cr_log_info("Testing empty value");
	cr_assert(var_parsing(&lst, "SUPER=") == 0, "failed when tested");
	cr_assert(lst != NULL, "lst left unset");
	cr_assert(lst->name != NULL, "name left unset");
	cr_assert(lst->value == NULL, "value left unitialized");
	cr_assert(eq(str, lst->name, "SUPER"), "name set wrong");
	cr_assert(lst->value == NULL, "value not NULL");
}
*/

Test(var, get_string, .description="Testing var_get_string", .fini = clean_lst)
{
	lst = NULL;
	char *a;
	a = var_get_string(lst);
	cr_assert(a == NULL, "failed when lst == NULL");
	cr_assert(var_parsing(&lst, "var=coucou") == 0, "failed parsing");
	a = var_get_string(lst);
	cr_assert(a != NULL, "failed");
	cr_assert(eq(str, a, "var=coucou"), "failed");
	free(a);
	cr_assert(var_parsing(&lst, "hello=again") == 0, "failed parsing");
	a = var_get_string(lst);
	cr_assert(a != NULL, "failed");
	cr_assert(eq(str, a, "hello=again"), "failed");
	free(a);
}

Test(var, get, .description="Testing var_get", .fini = clean_lst)
{
	lst = NULL;
	// unexpected
	cr_expect(var_get(lst, "coucou") == NULL, "Doesn't fail when no lst");
	cr_expect(var_get(lst, NULL) == NULL, "Doesn't fail when no lst nor name");
	// expected
	if (var_parsing(&lst, "hey=cestlajoie") || var_parsing(&lst, "coucou=jesuisheureux")
			|| lst == NULL)
		cr_fatal("init error");
	cr_expect(var_get(lst, NULL) == NULL, "Doesn't fail when no name");
	cr_expect(var_get(lst, "hello") == NULL, "returns something when name doesn't exists");
	cr_expect(var_get(lst, "coucou") == lst, "returns wrong struct");
}

Test(var, get_value, .description="Testing var_get_value", .fini=clean_lst)
{
	lst = NULL;
	// unexpected
	cr_expect(var_get_value(lst, "coucou") == NULL, "Doesn't fail when no lst");
	cr_expect(var_get_value(lst, NULL) == NULL, "Doesn't fail when no lst nor name");
	// expected
	if (var_parsing(&lst, "hey=cestlajoie")
			|| var_parsing(&lst, "eh=")
			|| var_parsing(&lst, "coucou=jesuisheureux")
			|| lst == NULL)
		cr_fatal("init error");
	cr_expect(var_get_value(lst, NULL) == NULL, "Doesn't fail when no name");
	cr_expect(var_get_value(lst, "hello") == NULL, "returns something when name doesn't exists");
	cr_expect(eq(str, var_get_value(lst, "coucou"), "jesuisheureux"), "returns wrong struct");
	cr_expect(eq(str, var_get_value(lst, "eh"), ""), "returns something when value empty");
}

Test(var, pop, .description="Testing poping values out of a list")
{
	t_lstvar	a;
	t_lstvar	b;

	lst = NULL;
	if (var_parsing(&lst, "hey=cestlajoie")
			|| var_parsing(&lst, "eh=")
			|| var_parsing(&lst, "coucou=jesuisheureux")
			|| lst == NULL)
		cr_fatal("init error");
	a = lst->next;
	cr_assert(eq(str, a->name, "eh"), "init error 2");
	cr_assert(eq(int, 0, var_pop(&lst, lst)), "pop error");
	cr_assert(eq(ptr, a, lst), "origin not correctly updated");
	b = lst->next;
	cr_assert(eq(int, 0, var_pop(&lst, b)), "pop error");
	cr_assert(eq(ptr, a, lst), "origin updated but not wanted");
	cr_assert(eq(int, 0, var_pop(&lst, lst)), "pop error");
	cr_assert(eq(ptr, NULL, lst), "origin not set to NULL when empty");
	cr_assert(eq(int, -1, var_pop(&lst, lst)), "pop did not fail");
	cr_assert(eq(ptr, NULL, lst), "origin not set to NULL when empty and failed");
}
