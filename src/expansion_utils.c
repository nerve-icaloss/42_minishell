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

int	handle_quotes(char **ret, t_node *args, int *i, int *j)
{
	static const char	quotes[3] = "'\"";
	int					k;

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
int	remove_quotes(t_node *args)
{
	char				*ret;
	int					i;
	int					j;

	if (!args)
		return (errno = ENODATA, -1);
	ret = NULL;
	i = 0;
	j = 0;
	while (args->val && args->val[i + j])
		if (handle_quotes(&ret, args, &i, &j))
			break ;
	if (args->val)
		free(args->val);
	args->val = ret;
	return (0);
}
