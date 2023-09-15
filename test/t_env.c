/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 18:09:15 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "criterion/criterion.h"
#include <stdio.h>

char *envp[] = {
	"coucou=jesuisla",
	"PWD=home",
	"HOME=home_but_there",
	"OLDPWD=was_there",
	"BUTYK=ok",
	"SUPER=",
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

Test(env, update_count, .description="Test of env_update_count", .init = setup) {
	cr_expect(myenv.count == 6, "Count is wrong after init");
	puts("Some more tests to write for update count");
}

Test(env, init, .description="Test of env_init", .fini = clean) {
	cr_assert(env_init(&myenv, envp));
}
