/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:10:43 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:06:02 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expander.h"

static int	expand_init(t_expand *expd, char *word)
{
	ft_memset(expd, 0, sizeof(*expd));
	expd->pstart = ft_strdup(word);
	if (!expd->pstart)
		return (errno = ENOMEM, -1);
	expd->p = expd->pstart;
	expd->in_double_quote = false;
	expd->expanded = false;
	return (0);
}

static char	*scan_word(char *data)
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
			buf++;
			return (ret);
		}
		buf++;
	}
	return (ret);
}

static void	split_word(t_node **origin, char *data)
{
	t_node	*new;
	char	*word;

	if (!origin || !data)
		return (errno = ENODATA, (void) NULL);
	word = scan_word(data);
	while (*word)
	{
		new = word_new(word);
		if (!new)
			return (node_sibling_clean(origin));
		node_sibling_add(origin, new);
		word = scan_word(NULL);
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
		word = word_new(expd.pstart);
		if (!word)
			return (NULL);
	}
	free(expd.pstart);
	remove_quotes(word);
	return (word);
}

t_node	*redir_expansion(char *data, t_redir_type type, t_myenv *env)
{
	t_node		*redir;
	t_expand	expd;

	if (!data || !*data || !env)
		return (errno = ENODATA, NULL);
	if (expand_init(&expd, data))
		return (NULL);
	find_expansion(&expd, env);
	redir = redir_new(expd.pstart, type);
	if (!redir)
		return (NULL);
	free(expd.pstart);
	if (type != HEREDOC)
		remove_quotes(redir);
	return (redir);
}
