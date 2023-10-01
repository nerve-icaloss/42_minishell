/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:32:32 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 19:33:57 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


t_myshell shell_init(void)
{
	t_myshell shell;

	shell.history = NULL;
	shell.readline = NULL;
	return (shell);
}

void	shell_clean(t_myshell *shell)
{
	free(shell->readline);
	history_clean(&shell->history);
	env_clean(&shell->env);
	exectree_clean(&shell->exectree);
}
