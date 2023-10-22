/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 17:04:51 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * there is no params needed
 * T */
int	env_builtin(t_myenv *env)
{
	t_lstvar	var;

	var = env->lst_var;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
	return (0);
}
