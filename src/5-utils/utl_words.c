/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:56:04 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 15:42:11 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	switch_words(t_node *a, t_node *b)
{
	char	*temp;

	if (!a || !b || a == b)
		return ;
	temp = a->val;
	a->val = b->val;
	b->val = temp;
}

size_t	get_max_len(t_node *i)
{
	size_t	len;

	len = 0;
	while (i)
	{
		if (ft_strlen(i->val) > len)
			len = ft_strlen(i->val);
		i = i->next_sibling;
	}
	return (len);
}

void	sort_words(t_node **word)
{
	t_node	*min;
	t_node	*i;
	t_node	*j;

	if (!word)
		return ;
	i = *word;
	while (i && i->next_sibling)
	{
		j = i->next_sibling;
		min = i;
		while (j)
		{
			if (ft_strcasecmp(j->val, min->val) < 0)
				min = j;
			j = j->next_sibling;
		}
		switch_words(i, min);
		i = i->next_sibling;
	}
}
