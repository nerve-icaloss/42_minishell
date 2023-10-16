/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 11:49:45 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <asm-generic/errno.h>

int	execute_cmd(t_node *cmd, t_myshell *shell)
{
	return (cmd->exit);
}

int	execute_pipe(t_node *pipe, t_myshell *shell)
{
	return (pipe->exit);
}

int	stop_execute(t_node *node)
{
	if (node->type == NODE_AND && node->exit > 0)
		return (1);
	if (node->type == NODE_OR && node->exit == 0)
		return (1);
	return (0);
}

int	execute_tree(t_node *root, t_myshell *shell)
{
	t_node	*child;
	t_node	*i;

	if (!root || !shell)
		return (errno = ENODATA, 1);
	if (root->type == NODE_PIPE)
		return (execute_pipe(root, shell));
	if (root->type == NODE_CMD)
		return (execute_cmd(root, shell));
	child = root->first_child;
	while(child)
	{
		i = child->next_sibling;
		root->exit = execute_tree(child, shell);
		if (stop_execute(root))
			return (root->exit);
		child = i;
	}
	return (root->exit);
}
