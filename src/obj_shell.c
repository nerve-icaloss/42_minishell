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


t_myshell new_shell(void)
{
	t_myshell shell;

	shell.history = NULL;
	shell.readline = NULL;
	return (shell);
}

void	clean_shell(t_myshell *shell)
{
	free(shell->readline);
	clean_history(&shell->history);
	clean_env(&shell->env);
	clean_exectree(&shell->exectree);
}
