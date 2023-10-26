/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:55:54 by nserve            #+#    #+#             */
/*   Updated: 2023/10/26 20:28:49 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * k == 0 means '
 * k == 1 means "
 * */
static int	remove_quotes_word(t_node *word)
{
	static const char	quotes[3] = "'\"";
	char				*i;
	char				*j;

	if (!word || !word->val)
		return (errno = ENODATA, 1);
	i = word->val;
	while (i && *i)
	{
		while (*i && !ft_strchr(quotes, *i))
			i++;
		if (!*i)
			return (0);
		j = ft_strchr(i + 1, *i);
		if (!j)
			return (0);
		ft_offset(j, 1);
		ft_offset(i, 1);
		//i = j - 2;
	}
	return (0);
}

int	remove_quotes(t_node *word)
{
	if (!word)
		return (errno = ENODATA, 1);
	while (word)
	{
		if (remove_quotes_word(word))
			return (1);
		word = word->next_sibling;
	}
	return (0);
}

int	remove_quotes_str(char **str)
{
	static const char	quotes[3] = "'\"";
	char				*i;
	char				*j;

	if (!str || !*str)
		return (errno = ENODATA, 1);
	i = *str;
	while (*i)
	{
		while (*i && !ft_strchr(quotes, *i))
			i++;
		if (!*i)
			return (0);
		j = ft_strchr(i + 1, *i);
		if (!*j)
			return (0);
		ft_offset(j, 1);
		ft_offset(i, 1);
		i = j - 2;
	}
	return (0);
}
