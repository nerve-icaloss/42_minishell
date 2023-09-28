/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/28 19:42:33 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include <stdio.h>

char *envp[] = {
	"coucou=jesuisla",
	"PWD=home",
	"HOME=home_but_there",
	"OLDPWD=was_there",
	"BUTYK=ok",
	"SUPER=",
	NULL
};
t_myenv	myenv;

void setup(void)
{
	if (env_init(&myenv, envp))
	{
		cr_log_warn("Problem with env_init... Skipping");
		cr_skip_test();
	}
}

void clean(void)
{
	env_clean(&myenv);
}

Test(env, update_count, .description="Test of env_update_count")
{
	myenv.lst_var = NULL;
	// unxepected
	cr_assert(env_update_count(NULL) != 0, "doesn't fail when no myenv");
	// expected
	cr_assert(env_update_count(&myenv) == 0, "fail when empty var_lst");
	cr_assert(myenv.count == 0, "count wrong when 0");
	cr_assert(var_parsing(&myenv.lst_var, "HELLO=cocou") == 0, "var manual setting problem");
	cr_assert(var_parsing(&myenv.lst_var, "hi=cc") == 0, "var manual setting problem");
	cr_assert(env_update_count(&myenv) == 0, "fail");
	cr_assert(myenv.count == 2, "count wrong when 2 with no empty values");
	cr_assert(var_parsing(&myenv.lst_var, "HI=") == 0, "var manual setting problem");
	cr_assert(env_update_count(&myenv) == 0, "fail when empty value");
	cr_assert(myenv.count == 2, "count wrong when 2 with empty values");
}

Test(env, init, .description="Test of env_init", .fini = clean) {
	cr_assert(env_init(&myenv, envp) == 0, "Init problem");
}

Test(env, clean, .description="Test of env_clean", .init = setup) {
	env_clean(&myenv);
	cr_expect(myenv.lst_var == NULL, "lst_var wasn't unset");
	cr_expect(myenv.envp == NULL, "envp wasn't unset");
	cr_expect(myenv.pwd == NULL, "pwd wasn't unset");
	cr_expect(myenv.oldpwd == NULL, "oldpwd wasn't unset");
	cr_expect(myenv.home == NULL, "home wasn't unset");
	cr_expect(myenv.count == 0, "count wasn't set to 0");
	//cleaning something clean
	env_clean(&myenv);
	cr_expect(myenv.lst_var == NULL, "lst_var wasn't unset");
	cr_expect(myenv.envp == NULL, "envp wasn't unset");
	cr_expect(myenv.pwd == NULL, "pwd wasn't unset");
	cr_expect(myenv.oldpwd == NULL, "oldpwd wasn't unset");
	cr_expect(myenv.home == NULL, "home wasn't unset");
	cr_expect(myenv.count == 0, "count wasn't set to 0");
}

Test(env, builtin, .description="tests for env (builtin)")
{
	cr_log_warn("env_builtin cannot be tested there. Test should be done manually");
}

int	env_default(t_myenv *myenv);

Test(env, default_values, .description="tests for env default")
{
	t_lstvar a;
	env_clean(&myenv);
	cr_assert(eq(int, 0, env_default(&myenv)));
	a = var_get(myenv.lst_var, "PWD");
	cr_assert(ne(ptr, NULL, a));
	a = var_get(myenv.lst_var, "OLDPWD");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(ptr, NULL, a->value));
	a = var_get(myenv.lst_var, "SHLVL");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(str, "1", a->value));
	// nothing
	env_clean(&myenv);
	var_parsing(&myenv.lst_var, "coucou=je suis heureux");
	var_parsing(&myenv.lst_var, "hello=je suis content");
	cr_assert(ne(ptr, myenv.lst_var, NULL));
	cr_assert(eq(str, myenv.lst_var->name, "hello"));
	cr_assert(eq(str, myenv.lst_var->next->name, "coucou"));
	cr_assert(eq(ptr, myenv.lst_var->next->next, NULL));
	// no PWD, OLDPWD or SHLVL are defined
	cr_assert(eq(int, 0, env_default(&myenv)));
	a = var_get(myenv.lst_var, "PWD");
	cr_assert(ne(ptr, NULL, a));
	a = var_get(myenv.lst_var, "OLDPWD");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(ptr, NULL, a->value));
	a = var_get(myenv.lst_var, "SHLVL");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(str, "1", a->value));
	// only no PWD
	env_clean(&myenv);
	var_parsing(&myenv.lst_var, "coucou=je suis heureux");
	var_parsing(&myenv.lst_var, "hello=je suis content");
	var_parsing(&myenv.lst_var, "PWD=here");
	cr_assert(eq(int, 0, env_default(&myenv)));
	a = var_get(myenv.lst_var, "PWD");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(str, "here", a->value), "pwd changed when already defined");
	a = var_get(myenv.lst_var, "OLDPWD");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(ptr, NULL, a->value));
	a = var_get(myenv.lst_var, "SHLVL");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(str, "1", a->value));
	// only SHLVL
	env_clean(&myenv);
	var_parsing(&myenv.lst_var, "coucou=je suis heureux");
	var_parsing(&myenv.lst_var, "hello=je suis content");
	var_parsing(&myenv.lst_var, "SHLVL=2");
	cr_assert(eq(int, 0, env_default(&myenv)));
	a = var_get(myenv.lst_var, "PWD");
	cr_assert(ne(ptr, NULL, a));
	a = var_get(myenv.lst_var, "OLDPWD");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(ptr, NULL, a->value));
	a = var_get(myenv.lst_var, "SHLVL");
	cr_assert(ne(ptr, NULL, a));
	cr_assert(eq(str, "3", a->value));
	// only OLDPWD
	cr_log_warn("Define OLDPWD alone expected behavoir");
}
