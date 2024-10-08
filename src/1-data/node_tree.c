/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:28:52 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:38:16 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	node_parent_add(t_node *child, t_node *parent)
{
	if (!child || !parent)
		return (errno = ENODATA, (void) NULL);
	parent->first_child = child;
	if (!child->parent)
		child->parent = parent;
	else
	{
		parent->parent = child->parent;
		child->parent = parent;
		if (!child->prev_sibling)
			parent->parent->first_child = parent;
		else
			parent->prev_sibling = child->prev_sibling;
		parent->next_sibling = child->next_sibling;
		child->prev_sibling = NULL;
		child->next_sibling = NULL;
	}
	parent->children++;
}

void	node_parent_insert(t_node *parent, t_node *child)
{
	t_node	*parent_last_child;

	if (!parent || !child)
		return (errno = ENODATA, (void) NULL);
	child->parent = parent;
	parent_last_child = parent->first_child;
	while (parent_last_child->next_sibling)
		parent_last_child = parent_last_child->next_sibling;
	child->first_child = parent_last_child;
	parent_last_child->parent = child;
	parent_last_child->prev_sibling->next_sibling = child;
	parent_last_child->prev_sibling = 0;
	child->children++;
}

void	node_child_add(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
		return (errno = ENODATA, (void) NULL);
	child->parent = parent;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
	parent->exit = child->exit;
}

void	node_tree_clean(t_node *node)
{
	t_node	*child;
	t_node	*i;

	if (!node)
		return (errno = ENODATA, (void) NULL);
	if (node->parent && node->parent->first_child == node)
	{
		if (node->next_sibling)
			node->parent->first_child = node->next_sibling;
		else
			node->parent->first_child = NULL;
	}
	child = node->first_child;
	while (child)
	{
		i = child->next_sibling;
		node_tree_clean(child);
		child = i;
	}
	if (node->parent)
		node->parent->children--;
	if (node->val)
		free(node->val);
	free(node);
}
