/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:51:15 by nserve            #+#    #+#             */
/*   Updated: 2023/10/19 10:32:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"

static void	return_builtin_lst(t_builtin **builtins)
{
	builtins[0]->name = ft_strdup("exit");
	builtins[0]->f = exit_builtin;
	builtins[1]->name = ft_strdup("cd");
	builtins[1]->f = cd_builtin;
	builtins[2]->name = ft_strdup("pwd");
	builtins[2]->f = pwd_builtin;
	builtins[3]->name = ft_strdup("env");
	builtins[3]->f = exit_builtin;
	builtins[4]->name = ft_strdup("export");
	builtins[4]->f = export_builtin;
	builtins[5]->name = ft_strdup("unset");
	builtins[5]->f = exit_builtin;
	builtins[6]->name = ft_strdup("echo");
	builtins[6]->f = exit_builtin;
	builtins[7]->name = NULL;
	builtins[7]->f = NULL;
}

int	find_builtin_f(t_execute *exec)
{
	t_builtin	**builtins;
	int			i;

	builtins = builtin_init();
	if (!exec || !builtins)
		return (errno = ENODATA, 1);
	return_builtin_lst(builtins);
	i = 0;
	while (builtins[i]->name != NULL)
	{
		if (ft_strncmp(exec->argv[0], builtins[i]->name,
				ft_strlen(builtins[i]->name)) == 0)
		{
			exec->builtin_f = builtins[i]->f;
			return (builtin_clean(builtins), 0);
		}
		i++;
	}
	return (builtin_clean(builtins), 0);
}
