/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:32:20 by nserve            #+#    #+#             */
/*   Updated: 2023/10/05 11:44:37 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	unget_char(t_source *src)
{
	if (src->curpos < 0)
		return ;
	src->curpos--;
}

char	next_char(t_source *src)
{
	if (!src || !src->buf)
		return (errno = ENODATA, EOF);
	if (src->curpos == INIT_SRC_POS)
		src->curpos = -1;
	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}
	return (src->buf[src->curpos]);
}

char	peek_char(t_source *src)
{
	long	pos;

	if (!src || !src->buf)
		return (errno = ENODATA, ERRCHAR);
	pos = src->curpos;
	if (pos == INIT_SRC_POS)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (EOF);
	return (src->buf[pos]);
}

void	skip_spaces(t_source *src)
{
	char	c;

	if (!src || !src->buf)
	{
		return ;
	}
	c = peek_char(src);
	while((c != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
		c = peek_char(src);
	}
}
