/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:53:24 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:38:42 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_numeric_arg(char *str, long long *ret)
{
	static const unsigned long long int	maxi = 0x8000000000000000;
	long long							signe;
	int									written;

	*ret = 0;
	written = 0;
	signe = 1;
	if (ft_strlen(str) > 20)
		return (0);
	while (*str)
	{
		if ('0' <= *str && *str <= '9' && (written || ++written))
			*ret = (*ret * 10) + (*str - '0');
		else if ((*str == '+' || *str == '-') && (!written && ++written))
			signe *= 1 - (2 * (*str / '-'));
		else if (!ft_isspace(*str) || written)
			break ;
		if (*ret < 0 && (signe > 0 || ft_memcmp(ret, &maxi, sizeof(long long))))
			return (0);
		str++;
	}
	*ret *= signe;
	return (!*str || ft_isspace(*str));
}

static int	check_exit_args(char *args[], long long *ret)
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
		if (!is_numeric_arg(args[i], ret))
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
	long long	ret;
	char		exit;

	exit = check_exit_args(args, &ret);
	if (exit)
		return (exit);
	exit = (char) ret;
	if (env->subsh == false)
	{
		g_signal = -1;
		write(2, "exit\n", 5);
	}
	if (!args[1])
		exit = *env->exit;
	return (exit);
}
