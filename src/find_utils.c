/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:56:44 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 18:56:51 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_utils.h"
#include "expand_var.h"

t_redir_type find_word_type(char *data)
{
	if (data[0] == '<' && data[1] == '\0')
		return (READ);
	else if (data[0] == '<' && data[1] == '<' && data[2] == '\0')
		return (HEREDOC);
	else if (data[0] == '>' && data[1] == ' ')
		return (TRUNC);
	else if (data[0] == '>' && data[1] == '<' && data[2] == '\0')
		return (APPEND);
	else
		return (WORD);

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

size_t find_closing_quote(char *data)
{
	char	quote;
	size_t	i;
	size_t	len;

	if (!data)
		return (errno = ENODATA, 0);
	quote = data[0];
	if(quote != '\'' && quote != '"')
		return (0);
	i = 0;
	len = strlen(data);
	while(++i < len)
		if(data[i] == quote)
			return (i);
	return (0);
}

size_t	find_closing_brace(char *data)
{
	size_t	ob_count;
	size_t	cb_count;
	size_t	len;
	size_t	i;

	if (!data || data[0] != '(')
		return (errno = ENODATA, 0);
	ob_count = 1;
	cb_count = 0;
	len = ft_strlen(data);
	i = 0;
	while (++i < len)
	{
		if ((data[i] == '"' || data[i] == '\''))
			i += find_closing_quote(data + i);
		if (data[i] == '(')
			ob_count++;
		if (data[i] == ')')
			cb_count++;
		if (ob_count == cb_count)
			break ;
	}
	if (ob_count != cb_count)
		return (0);
	return (i);
}
