/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:28 by nserve            #+#    #+#             */
/*   Updated: 2023/10/15 13:33:43 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <asm-generic/errno.h>

void	node_sibling_add(t_node **origin, t_node *child)
{
	t_node	*i;

	if (!origin || !child)
		return (errno = ENODATA, (void)NULL);
	i = *origin;
	while (i && i->next_sibling)
		i = i->next_sibling;
	if (!i)
		*origin = child;
	else
	{
		i->next_sibling = child;
		child->prev_sibling = i;
	}
}

void	node_sibling_pop(t_node *node)
{
	node->parent->children--;
	if (node->prev_sibling == NULL)
		node->parent->first_child = node->next_sibling;
	else
		node->prev_sibling->next_sibling = node->next_sibling;
	if (node->next_sibling)
		node->next_sibling->prev_sibling = node->prev_sibling;
	node_tree_clean(node);
}

void	node_sibling_clean(t_node **origin)
{
	t_node	*i;

	if (!origin)
		return (errno = ENODATA, (void)NULL);
	i = *origin;
	while (i)
	{
		*origin = (*origin)->next_sibling;
		if (i->first_child)
			node_tree_clean(i);
		else
		{
			if (i->val)
				free(i->val);
			free(i);
		}
		i = *origin;
	}
	*origin = NULL;
}
