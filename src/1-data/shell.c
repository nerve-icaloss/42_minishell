/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:32:32 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 19:33:57 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	shell_clean(t_myshell *shell)
{
	history_clean(&shell->hist);
	env_clean(&shell->env);
	node_tree_clean(shell->root);
}
