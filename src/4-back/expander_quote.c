/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:55:54 by nserve            #+#    #+#             */
/*   Updated: 2023/10/25 20:21:39 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	handle_quotes(char *src, int *i, int *j)
{
	static const char	quotes[3] = "'\"";
	int					k;
	char				*first;

	if (!src || !i || !j)
		return (1);
	while (src[*i + *j] && !strchr(quotes, src[*i + *j]))
		(*j)++;
	first = src + *i + *j;
	k = strchr(quotes, src[*i + *j]) - quotes;
	*i += *j + 1;
	*j = 0;
	while (src[*i + *j] && src[*i + *j] != quotes[k])
		(*j)++;
	if (src[*i + *j])
	{
		ft_offset(src + *i + *j, 1);
		ft_offset(first, 1);
	}
	*i += *j + 1;
	*j = 0;
	return (0);
}

/*
 * k == 0 means '
 * k == 1 means "
 * */
static int	remove_quotes_word(t_node *word)
{
	char				*ret;
	int					i;
	int					j;

	if (!word)
		return (errno = ENODATA, 1);
	ret = NULL;
	i = 0;
	j = 0;
	while (word->val && word->val[i + j])
		if (handle_quotes(word->val, &i, &j))
			break ;
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
	char				*ret;
	int					i;
	int					j;

	if (!str || !*str)
		return (errno = ENODATA, 1);
	ret = NULL;
	i = 0;
	j = 0;
	while (*str && *str[i + j])
		if (handle_quotes(*str, &i, &j))
			break ;
	return (0);
}
