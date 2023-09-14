/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:54:20 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 12:39:42 by hmelica          ###   ########.fr       */
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
	i = var_get(my.lst_var, "coucou");
	if (i)
		printf("Getting 'coucou' : %p\n'%s'='%s'\n", i, i->name, i->value);
	else
		printf("Coucou not found. : %p\n", i);
	printf("Coucou value only : %s\n", var_get_value(my.lst_var, "coucou"));
	var_clean(&my.lst_var);
	return (0);
}
