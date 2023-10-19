/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:23:00 by nserve            #+#    #+#             */
/*   Updated: 2023/10/19 11:42:21 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_node	*node_new(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (errno = ENOMEM, perror("node_init"), NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

int	node_val_set(t_node *node, char *val)
{
	if (!node)
		return (errno = ENODATA,  -1);
	if (!val)
	{
		node->val = NULL;
		printf("val empty:%s", val);
	}
	else
	{
		node->val =  ft_strdup(val);
		if (!node->val)
			return (errno = ENOMEM, perror("node_val_set"), -1);
	}
	return (0);
}

void	node_parent_add(t_node *child, t_node *parent)
{
	if (!child || !parent)
		return (errno = ENODATA, (void)NULL);
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
		return (errno = ENODATA, (void)NULL);
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
	t_node	*i;

	if (!parent || !child)
		return (errno = ENODATA, (void)NULL);
	child->parent = parent;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while(sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
	i = child->next_sibling;
	while (i)
	{
		i->parent = parent;
		parent->children++;
		i = i->next_sibling;
	}
}

void	node_tree_clean(t_node *node)
{
	t_node	*child;
	t_node	*i;

	if (!node)
		return (errno = ENODATA, (void)NULL);
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
