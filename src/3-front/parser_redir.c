/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:15:52 by nserve            #+#    #+#             */
/*   Updated: 2023/10/26 19:29:37 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void	parse_redir(t_token *tok, t_node *word)
{
	t_source *src;

	if (!tok || !word)
		return (errno =ENODATA, (void) NULL);
	src = tok->src;
	token_clean(tok);
	tok = tokenize(src);
	if (tok->type != TOK_WORD)
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_token(tok->type);
	}
	else if (find_word_type(tok->txt) != WORD)
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_redir(word->rtype);
	}
	else
		node_val_set(word, tok->txt);
	token_clean(tok);
}
