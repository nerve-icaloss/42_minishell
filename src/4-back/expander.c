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

static void	find_expansion(t_expand *expd, t_myenv *env)
{
	if (!expd || !env)
		return (errno = ENODATA, (void) NULL);
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
			expd->pstart = expd->p;
			expd->expanded = 1;
		}
		if (ft_isspace(*expd->p))
			expd->expanded = 1;
		expd->p++;
	}
}

t_node	*word_expand(char *data, t_myenv *env)
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

char *redir_expand(char *data, t_redir_type type, t_myenv *env)
{
	char		*ret;
	t_expand	expd;

	if (!data || !*data || !env)
		return (errno = ENODATA, NULL);
	if (type != HEREDOC)
	{
		if (expand_init(&expd, data))
			return (NULL);
		find_expansion(&expd, env);
		ret = ft_strdup(expd.pstart);
		if (!ret)
			return (errno = ENOMEM, NULL);
		free(expd.pstart);
		remove_quotes_str(&ret);
	}
	else
	{
		ret = ft_strdup("heredoc");
		if (!ret)
			return (errno = ENOMEM, NULL);
	}
	return (ret);
}
