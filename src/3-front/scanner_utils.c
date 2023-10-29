/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:26:05 by nserve            #+#    #+#             */
/*   Updated: 2023/10/25 16:04:12 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/scanner.h"

int	scan_quote(t_source *src)
{
	int	i;

	i = find_closing_quote(src->buf + src->curpos);
	if (!i)
	{
		src->tok_type = TOK_SYNTAX;
		if (src->buf[src->curpos] == '"')
			write(2, "minishell: syntax error near token `\"'\n", 40);
		if (src->buf[src->curpos] == '\'')
			write(2, "minishell: syntax error near token `\''\n", 40);
		return (ENDLOOP);
	}
	while (i--)
		tok_buf_add(src, next_char(src));
	return (0);
}

int	scan_verticalbar(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 1)
		return (tok_buf_pop(src), unget_char(src), ENDLOOP);
	nc = next_char(src);
	nc2 = peek_char(src);
	if ((nc == '|' && nc2 == '|') || (nc == ' ' && nc2 == '|'))
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_token(TOK_PIPE);
	}
	else if (nc == '|')
	{
		tok_buf_add(src, nc);
		src->tok_type = TOK_OR;
	}
	else
	{
		unget_char(src);
		src->tok_type = TOK_PIPE;
	}
	return (ENDLOOP);
}

int	scan_ampersand(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 1)
		return (tok_buf_pop(src), unget_char(src), ENDLOOP);
	nc = next_char(src);
	nc2 = peek_char(src);
	if (nc == '&' && nc2 == '&')
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_token(TOK_AND);
		return (ENDLOOP);
	}
	else if (nc == '&')
	{
		tok_buf_add(src, nc);
		src->tok_type = TOK_AND;
		return (ENDLOOP);
	}
	else
		unget_char(src);
	return (0);
}

int	scan_lessthan(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 1)
		return (tok_buf_pop(src), unget_char(src), ENDLOOP);
	src->tok_type = TOK_WORD;
	nc = next_char(src);
	nc2 = peek_char(src);
	if (nc == '<' && nc2 == '<')
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_redir(HEREDOC);
	}
	else if (nc == '<')
		tok_buf_add(src, nc);
	else
		unget_char(src);
	return (ENDLOOP);
}

int	scan_morethan(t_source *src, char nc)
{
	char	nc2;

	if (src->tok_bufindex > 1)
		return (tok_buf_pop(src), unget_char(src), ENDLOOP);
	src->tok_type = TOK_WORD;
	nc = next_char(src);
	nc2 = peek_char(src);
	if (nc == '>' && nc2 == '>')
	{
		src->tok_type = TOK_SYNTAX;
		syntax_error_redir(APPEND);
	}
	else if (nc == '>')
		tok_buf_add(src, nc);
	else
		unget_char(src);
	return (ENDLOOP);
}
