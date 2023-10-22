/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:55:54 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 18:56:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	handle_quotes(char **ret, t_node *args, int *i, int *j)
{
	static const char	quotes[3] = "'\"";
	int					k;

	if (!ret || !args || !i || !j)
		return (1);
	while (args->val[*i + *j] && !strchr(quotes, args->val[*i + *j]))
		(*j)++;
	*ret = ft_strjoin2(*ret, ft_substr(args->val, *i, *j), 1, 1);
	if (!args->val[*i + *j])
		return (1);
	k = strchr(quotes, args->val[*i + *j]) - quotes;
	*i += *j + 1;
	*j = 0;
	while (args->val[*i + *j] && args->val[*i + *j] != quotes[k])
		(*j)++;
	*ret = ft_strjoin2(*ret, ft_substr(args->val, *i, *j), 1, 1);
	if (!args->val[*i + *j])
		return (1);
	*i += *j + 1;
	*j = 0;
	return (0);
}

/*
 * k == 0 means '
 * k == 1 means "
 * */
static int	word_remove_quotes(t_node *word)
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
		if (handle_quotes(&ret, word, &i, &j))
			break ;
	if (word->val)
		free(word->val);
	word->val = ret;
	return (0);
}

int	remove_quotes(t_node *word)
{
	t_node	*child;

	if(!word)
		return (errno = ENODATA, 1);
	while (word)
	{
		if (word_remove_quotes(word))
			return (1);
		word = word->next_sibling;
	}
	return (0);
}
