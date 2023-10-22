/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:28 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 16:59:11 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_node	*word_new(char *data)
{
	t_node	*word;

	if (!data)
		return (errno = ENODATA, NULL);
	word = node_new(NODE_WORD);
	if (!word)
		return (errno = ENOMEM, NULL);
	if (node_val_set(word, data) == -1)
		return (node_tree_clean(word), NULL);
	word->rtype = WORD;
	return (word);
}

t_node	*redir_new(char *data, t_redir_type type)
{
	t_node	*redir;

	if (!data)
		return (errno = ENODATA, NULL);
	redir = node_new(NODE_WORD);
	if (!redir)
		return (errno = ENOMEM, NULL);
	if (node_val_set(redir, data) == -1)
		return (node_tree_clean(redir), NULL);
	redir->rtype = type;
	return (redir);
}

void	node_sibling_add(t_node **origin, t_node *child)
{
	t_node	*i;

	if (!origin || !child)
		return (errno = ENODATA, (void) NULL);
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
	if (node->prev_sibling == NULL)
		node->parent->first_child = node->next_sibling;
	else
		node->prev_sibling->next_sibling = node->next_sibling;
	if (node->next_sibling)
		node->next_sibling->prev_sibling = node->prev_sibling;
	if (!node->prev_sibling && !node->next_sibling)
		node->parent->first_child = NULL;
	node_tree_clean(node);
}

void	node_sibling_clean(t_node **origin)
{
	t_node	*i;

	if (!origin)
		return (errno = ENODATA, (void) NULL);
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
