/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:38:19 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:39:28 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

int	env_update_count(t_myenv *env);

t_myenv	myenv_p;

Test(envp, clean, .description="Test of envp_clean")
{
	// unexpected
	envp_clean(NULL);
	myenv_p.envp = NULL;
	envp_clean(&myenv_p.envp);
	cr_assert(myenv_p.envp == NULL, "envp set weirdly when NULL");
	// expected
	myenv_p.envp = malloc(sizeof(char *) * 3);
	if (!myenv_p.envp)
		cr_fatal("Malloc fail");
	myenv_p.envp[2] = NULL;
	myenv_p.envp[0] = malloc(sizeof(char) * 2);
	if (!myenv_p.envp[0])
	{
		free(myenv_p.envp);
		cr_fatal("malloc fail");
	}
	myenv_p.envp[1] = malloc(sizeof(char) * 2);
	if (!myenv_p.envp)
	{
		free(myenv_p.envp);
		free(myenv_p.envp[0]);
		cr_fatal("malloc fail");
	}
	envp_clean(&myenv_p.envp);
	cr_assert(myenv_p.envp == NULL);
}

void	clean_envp(void)
{
	envp_clean(&myenv_p.envp);
}

Test(envp, update, .description="Test of envp_update", .fini = clean_envp)
{
	// unexpected
	cr_log_info("Execpected situations");
	cr_assert(envp_update(NULL) != 0, "No fail when no myenv");
	// expected
	cr_log_info("Empty lst");
	myenv_p.lst_var = NULL;
	myenv_p.envp = NULL;
	myenv_p.count = 0;
	cr_assert(envp_update(&myenv_p) == 0, "Fail when not supposed to");
	cr_assert(myenv_p.envp != NULL, "envp not set when empty");
	if (*(myenv_p.envp) != NULL)
		cr_assert(1, "envp not set to NULL when empty");
	// filling up
	if (var_parsing(&myenv_p.lst_var, "coucou=jesuisheureux")
			|| var_parsing(&myenv_p.lst_var, "hello=hi"))
		cr_fatal("parsing fail");
	// filled with values
	cr_log_info("Filled with values");
	cr_assert(env_update_count(&myenv_p) == 0, "Fail when init counting");
	cr_assert(myenv_p.count == 2, "Count wrong");
	cr_assert(envp_update(&myenv_p) == 0, "Fail when not supposed to");
	cr_assert(myenv_p.envp != NULL, "envp unitialised");
	cr_assert(eq(str, myenv_p.envp[0], "hello=hi"), "value 0 wrong");
	cr_assert(eq(str, myenv_p.envp[1], "coucou=jesuisheureux"), "value 0 wrong");
	cr_assert(myenv_p.envp[2] == NULL, "last not NULL");
	// filled with no values
	if (var_parsing(&myenv_p.lst_var, "hey=")
			|| var_parsing(&myenv_p.lst_var, "bonjour=je_suis_moins"))
		cr_fatal("parsing fail");
	cr_assert(env_update_count(&myenv_p) == 0, "Fail when init counting");
	cr_assert(myenv_p.count == 3, "Count wrong");
	cr_log_info("Filled with some empty values");
	cr_assert(envp_update(&myenv_p) == 0, "Fail when not supposed to");
	cr_assert(myenv_p.envp != NULL, "envp unset");
	cr_assert(myenv_p.envp[0] != NULL, "envp[0] empty");
	cr_assert(eq(str, myenv_p.envp[0], "bonjour=je_suis_moins"), "value 0 wrong");
	cr_assert(myenv_p.envp[1] != NULL, "envp[0] empty");
	cr_assert(eq(str, myenv_p.envp[1], "hello=hi"), "value 0 wrong");
	cr_assert(myenv_p.envp[2] != NULL, "envp[0] empty");
	cr_assert(eq(str, myenv_p.envp[2], "coucou=jesuisheureux"), "value 0 wrong");
	cr_assert(myenv_p.envp[3] == NULL, "last not NULL");
}
