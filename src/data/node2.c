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
	if (!*origin)
		*origin = child;
	i = *origin;
	while (i->next_sibling)
		i = i->next_sibling;
	i->next_sibling = child;
	child->prev_sibling = i;
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
		free(i->val);
		free(i);
		i = *origin;
	}
	*origin = NULL;
}
