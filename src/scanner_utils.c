/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:26:05 by nserve            #+#    #+#             */
/*   Updated: 2023/10/06 11:26:12 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner_utils.h"

int	scan_quote(t_source *src, char nc)
{
	int	i;

	if (src->tok_bufindex > 0)
		return (unget_char(src), ENDLOOP);
	tok_buf_add(src, nc);
	i = 0; //find_closing_quote(src->buf + src->curpos);
	if (!i)
	{
		src->tok_type = TOK_SYNTAX;
		return (write(2, "syntax error", 12), ENDLOOP);
	}
	while (i--)
		tok_buf_add(src, next_char(src));
	return (ENDLOOP);
}

int	scan_verticalbar(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 0)
		return (unget_char(src), ENDLOOP);
	tok_buf_add(src, nc);
	nc = next_char(src);
	printf("while |: tok_buf=%s | tok_type=%d | index=%d | pos=%c\n", src->tok_buf, src->tok_type, src->tok_bufindex, src->buf[src->curpos]);
	nc2 = peek_char(src);
	if (nc == '|' && nc2 == '|')
	{
		src->tok_type = TOK_SYNTAX;
		return (write(2, "syntax error", 12), ENDLOOP);
	}
	if (nc == '|')
	{
		tok_buf_add(src, nc);
		src->tok_type = TOK_OR;
		return (ENDLOOP);
	}
	else
	{
		unget_char(src);
		src->tok_type = TOK_PIPE;
		return (ENDLOOP);
	}
	return (0);
}

int	scan_ampersand(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 0)
		return (unget_char(src), ENDLOOP);
	tok_buf_add(src, nc);
	nc = next_char(src);
	printf("while &: tok_buf=%s | tok_type=%d | index=%d | pos=%c\n", src->tok_buf, src->tok_type, src->tok_bufindex, src->buf[src->curpos]);
	nc2 = peek_char(src);
	if (nc == '&' && nc2 == '&')
	{
		src->tok_type = TOK_SYNTAX;
		return (write(2, "syntax error", 12), ENDLOOP);
	}
	if (nc == '&')
	{
		tok_buf_add(src, nc);
		src->tok_type = TOK_AND;
		return (ENDLOOP);
	}
	return (0);
}

int	scan_lessthan(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 0)
		return (unget_char(src), ENDLOOP);
	tok_buf_add(src, nc);
	nc = next_char(src);
	printf("while <: tok_buf=%s | tok_type=%d | index=%d | pos=%c\n", src->tok_buf, src->tok_type, src->tok_bufindex, src->buf[src->curpos]);
	nc2 = peek_char(src);
	if (nc == '<' && nc2 == '<')
	{
		src->tok_type = TOK_SYNTAX;
		return (write(2, "syntax error", 12), ENDLOOP);
	}
	if (nc == '<')
	{
		tok_buf_add(src, nc);
		if (nc2 == ' ')
		{
			nc2 = next_char(src);
			tok_buf_add(src, nc2);
		}
		src->tok_type = TOK_WORD;
	}
	return (0);
}

int	scan_morethan(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 0)
		return (unget_char(src), ENDLOOP);
	tok_buf_add(src, nc);
	nc = next_char(src);
	printf("while >: tok_buf=%s | tok_type=%d | index=%d | pos=%c\n", src->tok_buf, src->tok_type, src->tok_bufindex, src->buf[src->curpos]);
	nc2 = peek_char(src);
	if (nc == '>' && nc2 == '>')
	{
		src->tok_type = TOK_SYNTAX;
		return (write(2, "syntax error", 12), ENDLOOP);
	}
	if (nc == '>')
	{
		tok_buf_add(src, nc);
		if (nc2 == ' ')
		{
			nc2 = next_char(src);
			tok_buf_add(src, nc2);
		}
		src->tok_type = TOK_WORD;
	}
	return (0);
}
