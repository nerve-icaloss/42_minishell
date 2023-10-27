/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:10:43 by nserve            #+#    #+#             */
/*   Updated: 2023/10/27 22:19:41 by hmelica          ###   ########.fr       */
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
		if (ft_isquote(*buf))
			buf = find_closing_quote(buf) + buf;
		else if (ft_isspace(*buf))
		{
			*buf = '\0';
			buf++;
			return (ret);
		}
		buf += (*buf != '\0');
	}
	return (ret);
}

static void	split_word(t_node **origin, char *data)
{
	t_node	*new;
	char	*word;

	if (!origin || !data)
		return (errno = ENODATA, (void) NULL);
	if (*data == '\0')
	{
		free(data);
		return (word_pop(origin, *origin));
	}
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

/*
 * gestion des variables
 * */
static void	find_expansion(t_expand *expd, t_myenv *env)
{
	char	*prec;
	size_t	prec_len;

	prec = expd->pstart;
	prec_len = ft_strlen(prec);
	var_expansion(&expd->pstart, env);
	expd->p = expd->pstart;
	if (expd->pstart != prec || prec_len != ft_strlen(expd->pstart))
		expd->expanded = 1;
}

/*
 * Returns null in case of problem
 * */
t_node	*word_expand(char *data, t_myenv *env)
{
	t_node		*word;
	t_expand	expd;
	int			wc_trigger;

	if (!data || !*data || !env)
		return (errno = ENODATA, NULL);
	if (expand_init(&expd, data))
		return (NULL);
	find_expansion(&expd, env);
	word = NULL;
	if (expd.expanded)
		split_word(&word, expd.pstart);
	else if (!word)
		word = word_new(expd.pstart);
	if (!word)
		return (NULL);
	free(expd.pstart);
	wc_trigger = !is_in_between_quotes(word->val);
	remove_quotes(word);
	if (wc_trigger && run_wildcard(&word, env->lst_var))
		return (node_tree_clean(word), NULL);
	return (word);
}

char	*redir_expand(char *data, t_redir_type type, t_myenv *env)
{
	char		*ret;
	t_expand	expd;

	if (!env)
		return (errno = ENODATA, NULL);
	if (type != HEREDOC)
	{
		if (!data)
			return (errno = ENODATA, NULL);
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
