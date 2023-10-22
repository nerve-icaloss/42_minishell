/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:53:24 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:05:00 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	exit_builtin(char *args[], t_myshell *shell)
{
	int	ret;

	ret = ft_atoi(args[1]);
	if (shell->env.subsh)
		return (ret);
	else
	{
		shell_clean(shell);
		exit(ret);
	}
}
