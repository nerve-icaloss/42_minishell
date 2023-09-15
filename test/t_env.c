/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 18:00:16 by hmelica          ###   ########.fr       */
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
	"BUTYK=ok"
};
t_myenv	myenv;

void env_clean_setup(void)
{
	if (env_init(&myenv, envp))
	{
		cr_log_warn("Problem with env_init but not tested yet... Skipping");
		cr_skip_test();
	}
}

Test(simple, env_clean, .description="Test of env_clean", .init = env_clean_setup) {
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
