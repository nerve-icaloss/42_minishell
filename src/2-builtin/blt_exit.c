/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:53:24 by nserve            #+#    #+#             */
/*   Updated: 2023/10/27 17:32:34 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_numeric_arg(char *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	if (data[i] == '-' || data[i] == '+')
		i++;
	while (data[i])
	{
		if (i > 19)
			ret = 0;
		if (!ft_isdigit(data[i]))
			ret = 0;
		i++;
	}
	return (ret);
}

static int	check_exit_args(char *args[])
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (i == 2)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		if (!is_numeric_arg(args[i]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				 args[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int	exit_builtin(char *args[], t_myenv *env)
{
	char	exit;

	exit = check_exit_args(args);
	if (exit)
		return (exit);
	if (env->subsh == false)
		g_signal = -1;
	if (args[1])
		exit = ft_atol(args[1]);
	else
		exit = *env->exit;
	return (exit);
}
