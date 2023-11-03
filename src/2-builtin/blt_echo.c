/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:24:31 by hmelica           #+#    #+#             */
/*   Updated: 2023/11/03 14:05:41 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
#include <stdlib.h>
int	main(int ac, char ** av)
{
	char	**tab;
	int		i;

	if (ac < 1)
		return (3);
	tab = calloc((ac + 1), sizeof(char *));
	if (!tab)
		return (-1);
	i = ac;
	while (--i >= 0)
		tab[i] = ft_strdup(av[i]);
	echo_builtin(tab);
	i = ac;
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	return (0);
}
*/

/*
 * ret = 1 if -n there
 * */

int	is_nl_flag(char *s)
{
	if (!s || *s != '-')
		return (0);
	s++;
	if (*s != 'n')
		return (0);
	while (*s == 'n')
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

int	flag_parkour(char ***argv)
{
	int	ret;
	int	is_flag;

	is_flag = 0;
	ret = is_nl_flag(**argv);
	if (ret)
		is_flag = 1;
	while (ret)
	{
		(*argv)++;
		ret = is_nl_flag(**argv);
		if (ret)
			is_flag = 1;
	}
	return (is_flag);
}

int	echo_builtin(char **argv, t_myenv *env)
{
	char	ret;
	char	*end;

	(void) env;
	if (!argv || !*argv)
		return (-1);
	argv++;
	if (!*argv)
		if (write(1, "\n", 1) < 0)
			return (ft_dprintf(2, "minishell: echo: %s\n", strerror(errno)));
	if (!*argv)
		return (0);
	ret = flag_parkour(&argv);
	while (*argv)
	{
		end = " ";
		if (!argv[1] && ret)
			end = "";
		else if (!argv[1])
			end = "\n";
		if (ft_printf("%s%s", *argv, end) < 0)
			return (ft_dprintf(2, "minishell: echo: %s\n", strerror(errno)), 1);
		argv++;
	}
	return (0);
}
