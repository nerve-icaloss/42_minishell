/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:26:12 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 14:48:30 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/scanner.h"

int	scan_space(t_source *src)
{
	if (src->tok_bufindex > 1)
	{
		if (src->tok_type == (t_tok_type)-1)
			src->tok_type = TOK_WORD;
		return (ENDLOOP);
	}
	return (0);
}

int	scan_bracket(t_source *src, char nc)
{
	if (src->tok_bufindex > 1)
		return (tok_buf_pop(src), unget_char(src), ENDLOOP);
	if (nc == '(')
		src->tok_type = TOK_BRACKET;
	if (nc == ')')
		src->tok_type = TOK_EOB;
	return (ENDLOOP);
}

static void	scan_token_from_source(t_source *src)
{
	char	nc;

	skip_spaces(src);
	nc = next_char(src);
	while (nc != EOF)
	{
		if (!ft_isspace(nc))
			tok_buf_add(src, nc);
		if ((nc == '"' || nc == '\'') && scan_quote(src) == ENDLOOP)
			break ;
		else if ((nc == '(' || nc == ')') && scan_bracket(src, nc) == ENDLOOP)
			break ;
		else if (nc == '|' && scan_verticalbar(src, nc) == ENDLOOP)
			break ;
		else if (nc == '&' && scan_ampersand(src, nc) == ENDLOOP)
			break ;
		else if (nc == '<' && scan_lessthan(src, nc) == ENDLOOP)
			break ;
		else if (nc == '>' && scan_morethan(src, nc) == ENDLOOP)
			break ;
		else if (ft_isspace(nc) && scan_space(src) == ENDLOOP)
			break ;
		nc = next_char(src);
	}
	//if (src->tok_bufindex > 0 && src->tok_type == (t_tok_type)-1)
	//	src->tok_type = TOK_WORD;
}


t_token	*tokenize(t_source *src)
{
	t_token		*tok;
	t_token		*tok_eof;

	tok_eof = token_ops_new(TOK_EOF);
	tok_eof->src = src;
	if (!src || !src->buf || !src->bufsize)
		return (errno = ENODATA, tok_eof);
	if (!src->tok_buf)
		return (tok_eof);
	tok_buf_reset(src);
	scan_token_from_source(src);
	if (src->tok_bufindex == 0)
		return (tok_eof);
	if (src->tok_bufindex >= src->tok_bufsize)
		(src->tok_bufindex)--;
	src->tok_buf[src->tok_bufindex] = '\0';
	if (src->tok_type == TOK_WORD)
		tok = token_word_new(src->tok_buf);
	else
	 	tok = token_ops_new(src->tok_type);
	if (!tok)
		return (errno = ENOMEM, perror("tokenize"), tok_eof);
	free(tok_eof);
	tok->src = src;
	return (tok);
}

void	untokenize(t_source *src)
{
	if (!src || !src->tok_buf || !src->tok_bufindex)
		return (errno = ENODATA, (void)NULL);
	while ((src->tok_bufindex)--)
		unget_char(src);
}
