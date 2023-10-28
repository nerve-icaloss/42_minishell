/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:03:11 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 23:21:16 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

void	handle_error_bracket(t_node *parent, t_token *tok)
{
	t_source	*src;

	if (!parent || !tok)
		return (errno = ENODATA, (void) NULL);
	src = tok->src;
	if (tok->type == TOK_EOF && parent->exit == 2)
		return ;
	if (tok->type == TOK_EOF && !parent->exit)
	{
		syntax_error_node(NODE_BRACKET);
		parent->exit = 2;
	}
	if (!parent->exit && parent->children < 1)
	{
		syntax_error_token(TOK_EOB);
		parent->exit = 2;
	}
}

void	handle_error_lvl(t_node *parent, t_token *tok, int type)
{
	t_source	*src;

	if (!parent || !tok)
		return (errno = ENODATA, (void) NULL);
	src = tok->src;
	if (type < tok->type && tok->type < TOK_EOF)
		untokenize(src);
	if (tok->type == TOK_SYNTAX)
		parent->exit = 2;
	if (!parent->exit && parent->children < 2 && type >= NODE_PIPE)
	{
		syntax_error_node(type);
		parent->exit = 2;
	}
	token_clean(tok);
}
