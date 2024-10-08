/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:00:47 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:41:56 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_fork(t_node *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == SYS_FAIL)
		cmd->exit = 1;
}
