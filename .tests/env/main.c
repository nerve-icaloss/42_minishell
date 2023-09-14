/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:54:20 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 12:11:02 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int ac, char **av, char **envp)
{
	t_myenv		my;
	t_lstvar	i;

	(void) ac;
	(void) av;
	printf("return value = %d\n", env_init(&my, envp));
	i = my.lst_var;
	while (i)
	{
		printf("'%s' = '%s'\n", i->name, i->value);
		i = i->next;
	}
	var_clean(&my.lst_var);
	return (0);
}
