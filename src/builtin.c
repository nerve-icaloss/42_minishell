/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:51:15 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 17:51:18 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	return_builtin_lst(t_builtin **builtin)
{
	ft_memset(*builtin, 0, 8 * sizeof(*builtin));
	builtin[0]->name = "exit";
	builtin[0]->f = exit_builtin;
	builtin[1]->name = "cd";
	builtin[1]->f = cd_builtin;
	builtin[2]->name = "pwd";
	builtin[2]->f = pwd_builtin;
	builtin[3]->name = "env";
	builtin[3]->f = env_builtin;
	builtin[4]->name = "export";
	builtin[4]->f = export_builtin;
	builtin[5]->name = "unset";
	builtin[5]->f = unset_builtin;
	builtin[6]->name = "echo";
	builtin[6]->f = echo_builtin;
	builtin[7]->name = NULL;
	builtin[7]->f = NULL;
}

int	find_builtin_f(t_execute *exec)
{
	t_builtin	*builtins;
	int			i;

	builtins = malloc(sizeof(*builtins) * 8);
	if (!builtins)
		return (errno = ENOMEM, exec->exit = 1, 1);
	return_builtin_lst(&builtins);
	i = 0;
	while (builtins[i].name != NULL)
	{
		if (strcmp(exec->argv[0], builtins[i].name) == 0)
		{
			exec->blt = builtins[i].f;
			return (free(builtins), 0);
		}
		i++;
	}
	return (free(builtins), 0);
}
