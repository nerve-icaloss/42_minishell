/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:55:54 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 18:56:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expansion_utils.h"

int	expand_init(t_expand *expd, char *word)
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

/*
 * k == 0 means '
 * k == 1 means "
 * */
int	remove_quotes(t_node *args)
{
	static const char	quotes[3] = "'\"";
	char				*s;
	char				*ret;
	int					i;
	int					j;
	int					k;

	if (!args)
		return (errno = ENODATA, -1);
	s = args->val;
	ret = NULL;
	i = 0;
	j = 0;
	while (s && s[i + j])
	{
		while (s[i + j] && !strchr(quotes, s[i + j]))
			j++;
		k = strchr(quotes, s[i + j]) - quotes;
		ret = ft_strjoin2(ret, ft_substr(s, i, j), 1, 1);
		if (!s[i + j])
			break ;
		i += j + 1;
		j = 0;
		while (s[i + j] && s[i + j] != quotes[k])
			j++;
		ret = ft_strjoin2(ret, ft_substr(s, i, j), 1, 1);
		if (!s[i + j])
			break ;
		i += j + 1;
		j = 0;
	}
	if (args->val)
		free(args->val);
	args->val = ret;
	return (0);
}
