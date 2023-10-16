/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:10:43 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 11:08:58 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_word.h"
#include "expansion_utils.h"
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
	word->redir = WORD;
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

	if (!origin || !data)
		return (errno = ENODATA, (void)NULL);
	word = 	find_word(data);
	while (*word)
	{
		new = new_word(word);
		if (!new)
			return (node_sibling_clean(origin));
		node_sibling_add(origin, new);
		word = find_word(NULL);
	}
}

t_node	*word_expansion(char *data, t_myenv *env)
{
	t_node		*word;
	t_expand	expd;
	
	if (!data || !*data || !env)
		return (errno = ENODATA, NULL);
	if (expand_init(&expd, data))
		return (NULL);
	find_expansion(&expd, env);
	word = NULL;
	if (expd.expanded)
		split_word(&word, expd.pstart);
	if (!word)
	{
		word = new_word(expd.pstart);
		if (!word)
			return (NULL);
	}
	free(expd.pstart);
	//remove_quotes(word);
	return (word);
}
