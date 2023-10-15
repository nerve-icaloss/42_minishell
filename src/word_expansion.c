/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:10:43 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 17:10:50 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include "expand_utils.h"
#include "expand_var.h"
#include "find_utils.h"

t_node	*new_word(char *data)
{
	t_node	*word;

	if (!data)
		return (errno = ENODATA, NULL);
	word = node_new(NODE_WORD);
	if (!word)
		return (errno = ENOMEM, NULL);
	if (node_val_set(word, data) == -1)
		return (node_tree_clean(word), NULL);
	return (word);
}

char	*find_word(char *data)
{
	static char	*buf;
	char		*ret;

	if (data)
		buf = data;
	while (ft_isspace(*buf))
		buf++;
	ret = buf;
	while (*buf)
	{
		if (ft_isspace(*buf))
		{
			*buf = '\0';
			return (ret);
		}
		buf++;
	}
	return (ret);
}

void	split_word(t_node **origin, char *data)
{
	t_node	*new;
	char	*word;
	int		i;

	if (!origin || !data)
		return (errno = ENODATA, (void)NULL);
	word = 	find_word(data);
	while (word != NULL)
	{
		new = new_word(word);
		if (!new)
			return (node_sibling_clean(origin));
		node_sibling_add(origin, new);
		word = find_word(NULL);
	}
}

void	find_expansion(t_expand *expd, t_myenv *env)
{
	if (!expd || !env)
		return (errno = ENODATA, (void)NULL);
	while (*expd->p)
	{
		if (*expd->p == '"')
			expd->in_double_quote = !expd->in_double_quote;
		if (*expd->p == '\'')
			if (!expd->in_double_quote)
				expd->p += find_closing_quote(expd->p);
		if (*expd->p == '$')
		{
			var_expansion(&expd->p, env);
			expd->expanded = 1;
		}
		if (ft_isspace(*expd->p))
			expd->expanded = 1;
		expd->p++;
	}
}

t_node	*word_expansion(char *orig_arg, t_myenv *env)
{
	t_node		*word;
	t_expand	expd;
	
	if (!orig_arg || !*orig_arg)
		return (errno = ENODATA, NULL);
	if (!expand_init(&expd, orig_arg))
		return (NULL);
	find_expansion(&expd, env);
	word = NULL;
	if (expd.expanded)
		split_word(&word, expd.pstart);
	if (!word)
	{
		word = new_word(expd.pstart);
		if (!word)
			return (errno = ENOMEM, NULL);
	}
	free(expd.pstart);
	//remove_quotes(word);
	return (word);
}
