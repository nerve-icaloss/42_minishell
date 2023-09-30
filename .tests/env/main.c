/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:54:20 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 10:25:29 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int ac, char **av, char **envp)
{
	t_myenv		my;
	t_lstvar	i;
	int			ret;

	(void) av;
	printf("# DEBUG # : env_init return value = %d\n", env_init(&my, envp));
	if (ac > 1)
	{
		ret = env_builtin(&my);
		var_clean(&my.lst_var);
		return (ret);
	}
	i = my.lst_var;
	while (i)
	{
		printf("'%s' = '%s'\n", i->name, i->value);
		i = i->next;
	}
	i = var_get(my.lst_var, "coucou");
	if (i)
		printf("# DEBUG # : Getting 'coucou' : %p\n'%s'='%s'\n", i, i->name, i->value);
	else
		printf("# DEBUG # : Coucou not found. : %p\n", i);
	printf("# DEBUG # : Coucou value only : %s\n", var_get_value(my.lst_var, "coucou"));
	var_clean(&my.lst_var);
	return (0);
}
