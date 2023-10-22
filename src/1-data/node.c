/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:23:00 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:00:20 by nserve           ###   ########.fr       */
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
	node->fd[IN] = -1;
	node->fd[OUT] = -1;
	node->pid = -1;
	node->rtype = -1;
	return (node);
}

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

int	node_val_set(t_node *node, char *val)
{
	if (!node)
		return (errno = ENODATA, -1);
	if (!val)
	{
		node->val = NULL;
		printf("val empty:%s", val);
	}
	else
	{
		node->val = ft_strdup(val);
		if (!node->val)
			return (errno = ENOMEM, perror("node_val_set"), -1);
	}
	return (0);
}
