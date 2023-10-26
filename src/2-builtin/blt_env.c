/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/26 19:12:05 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * there is no params needed
 * T */
int	env_builtin(char *argv[], t_myenv *env)
{
	t_lstvar	var;

	(void) argv;
	if (!env)
		return (errno = ENODATA, 1);
	var = env->lst_var;
	while (var && var->next)
		var = var->next;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->name, var->value);
		var = var->prev;
	}
	return (0);
}
