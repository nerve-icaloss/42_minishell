/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:14:00 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:03:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*token_word_new(char *str)
{
	t_token	*tok;

	tok = malloc(sizeof(*tok));
	if (!tok)
		return (errno = ENOMEM, perror("token_word_new"), NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->len = ft_strlen(str);
	tok->txt = ft_strdup(str);
	if (!tok->txt)
		return (errno = ENOMEM, perror("token_word_new"), free(tok), NULL);
	tok->type = TOK_WORD;
	return (tok);
}

t_token	*token_ops_new(t_tok_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(*tok));
	if (!tok)
		return (errno = ENOMEM, perror("token_ops_new"), NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->type = type;
	return (tok);
}

void	token_clean(t_token *tok)
{
	if (tok->txt)
		free(tok->txt);
	free(tok);
}
