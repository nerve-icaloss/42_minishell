/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:33:51 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 16:56:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_builtin	**builtin_init(void)
{
	t_builtin	**builtins;
	int			i;

	builtins = malloc(sizeof(t_builtin *) * 8);
	if (!builtins)
		return (errno = ENOMEM, NULL);
	i = 0;
	while (i < 8)
	{
		builtins[i] = malloc(sizeof(t_builtin));
		if (!builtins[i])
			errno = ENOMEM;
		i++;
	}
	if (errno == ENOMEM)
		return (builtin_clean(builtins), NULL);
	return (builtins);
}

void	builtin_clean(t_builtin **builtins)
{
	int	x;

	x = 0;
	while (builtins[x]->name)
	{
		free(builtins[x]->name);
		free(builtins[x]);
		x++;
	}
	free(builtins[x]);
	free(builtins);
}
