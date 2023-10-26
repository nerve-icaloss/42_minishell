/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:41:38 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/26 20:53:05 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_quotes(char *i[2], char *j[2], char *line, char *k);

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
 * returns 1 if in between quotes
 * */
int	is_in_between_quotes(char *s)
{
	char	*i[2];
	char	*j[2];
	char	*k;
	if (!s)
		return (0);
	k = ft_strchr(s, '*');
	while (k)
	{
		update_quotes(i, j, s, k);
		if ((i[0] && i[1] && i[0] < k && i[1] > k)
			|| (j[0] && j[1] && j[0] < k && j[1] > k))
			return (1);
		k = ft_strchr(k + 1, '*');
	}
	return (0);
}

int	run_wc_on(char *val, t_node **word, t_myvar *var)
{
	t_wildcard	*wc;
	char		*s;

	if (!val)
		return (-1);
	s = NULL;
	if (!var || home_expand(val, &s, var_get(var, "HOME")) || !s)
		return (ft_dprintf(2, "minishell: HOME not set\n"), -1);
	wc = generate_wildcard(s);
	free(s);
	if (wc)
	{
		if (wc_into_node(wc, word))
			return (wc_clean(&wc), -1);
	}
	if (!*word)
		*word = word_new(val);
	wc_clean(&wc);
	return (0);
}

/*
 * word should have no parent
 * */
int	run_wildcard(t_node **word, t_myvar *var)
{
	t_node		*i;
	t_node		*j;
	t_node		*end;

	if (!word)
		return (errno = ENODATA, -1);
	i = *word;
	end = i;
	while (end->next_sibling)
		end = end->next_sibling;
	while (i)
	{
		if (run_wc_on(i->val, word, var))
			return (-1);
		if (i != end)
			j = i->next_sibling;
		else
			j = NULL;
		if ((*word)->next_sibling)
			word_pop(word, i);
		i = j;
	}
	return (0);
}
