/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:41:38 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/25 12:53:58 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*char	*wc_to_str(t_wildcard *wc)
{
	char		*s;
	char		*a;
	t_wildcard	*child;

	if (!wc)
		return (NULL);
	s = NULL;
	child = wc->child;
	while (child)
	{
		a = wc_to_str(child);
		if (s && a)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, a, 1, 0);
		child = child->next;
	}
	child = wc;
	if (child && !child->wc)
	{
		if (s)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, child->s, 1, 0);
		child = child->next;
	}
	return (s);
}*/

int	wc_into_node(t_wildcard *wc, t_node **word)
{
	t_wildcard	*child;
	t_node		*to_add;

	if (!wc)
		return (-1);
	child = wc->child;
	while (child)
	{
		if (wc_into_node(child, word))
			return (-1);
		child = child->next;
	}
	child = wc;
	if (child && !child->wc)
	{
		to_add = word_new(child->s);
		if (!to_add)
			return (errno = ENOMEM, -1);
		node_sibling_add(word, to_add);
		child = child->next;
	}
	return (0);
}

/*
 * s should be one single path, with only alphanum and / and *
 * s will not be freed inside this function
 * */
t_wildcard	*generate_wildcard(char *s)
{
	char		*string;
	t_wildcard	*wc;

	if (!s)
		return (errno = ENODATA, NULL);
	wc = NULL;
	string = ft_strdup(s);
	if (wc_add(&wc, string))
		return (NULL);
	if (wc_rec_expand(wc))
		return (wc_clean(&wc), NULL);
	return (wc);
}

/*
 * word should have no parent
 * */
int	run_wildcard(t_node **word)
{
	t_node		*i;
	t_node		*j;
	t_node		*end;
	t_wildcard	*wc;

	if (!word)
		return (errno = ENODATA, -1);
	i = *word;
	end = i;
	while (end->next_sibling)
		end = end->next_sibling;
	while (i)
	{
		wc = generate_wildcard(i->val);
		if (wc)
			if (wc_into_node(wc, word))
				return (wc_clean(&wc), -1);
		wc_clean(&wc);
		if (i != end)
			j = i->next_sibling;
		else
			j = NULL;
		word_pop(word, i);
		i = j;
	}
	return (0);
}
