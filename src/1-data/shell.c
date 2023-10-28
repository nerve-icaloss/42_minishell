/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:32:32 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:31:08 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	shell_clean(t_myshell *shell)
{
	if (shell->hist)
		history_clean(&shell->hist);
	if (shell->root)
		node_tree_clean(shell->root);
	if (shell->start_dir)
		free(shell->start_dir);
	env_clean(&shell->env);
}
