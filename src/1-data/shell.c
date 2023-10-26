/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:32:32 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:00:57 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <unistd.h>

void	shell_clean(t_myshell *shell)
{
	if (shell->hist)
		history_clean(&shell->hist);
	if (shell->root)
		node_tree_clean(shell->root);
	env_clean(&shell->env);
	//close(STDIN_FILENO);
}
