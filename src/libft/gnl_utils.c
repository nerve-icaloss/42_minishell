/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:55:07 by hmelica           #+#    #+#             */
/*   Updated: 2023/07/20 13:02:14 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buffer	*buffer_remove(t_buffer *b)
{
	t_buffer	*next;

	next = b->next;
	if (next)
		next->last = b->last;
	free(b->data);
	free(b);
	return (next);
}

t_buffer	*buffer_clean(t_buffer **b)
{
	while (*b)
		*b = buffer_remove(*b);
	return (NULL);
}

t_buffer	*buffer_new(t_buffer **b)
{
	t_buffer	*new;

	new = malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->n = 0;
	new->data = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new->data)
	{
		free(new);
		return (buffer_clean(b));
	}
	ft_memset(new->data, '\0', BUFFER_SIZE + 1);
	new->last = new;
	if (!*b)
		*b = new;
	else
	{
		(*b)->last = new;
		while ((*b)->next)
			*b = (*b)->next;
		(*b)->next = new;
	}
	return (new);
}
