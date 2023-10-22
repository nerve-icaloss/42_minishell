/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:48:28 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:01:48 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	tok_buf_init(t_source *src)
{
	ft_memset(src, 0, sizeof(*src));
	src->tok_bufsize = 1024;
	src->tok_buf = malloc(sizeof(char) * src->tok_bufsize);
	if (!src->tok_buf)
		return (errno = ENOMEM, -1);
	ft_memset(src->tok_buf, '\0', src->tok_bufsize);
	return (0);
}

void	tok_buf_reset(t_source *src)
{
	src->tok_bufindex = 0;
	ft_memset(src->tok_buf, '\0', src->tok_bufsize);
	src->tok_type = 1;
}

void	tok_buf_add(t_source *src, char c)
{
	char	*tmp;

	src->tok_buf[src->tok_bufindex++] = c;
	if (src->tok_bufindex >= src->tok_bufsize)
	{
		tmp = realloc(src->tok_buf, src->tok_bufsize * 2);
		if (!tmp)
			return (errno = ENOMEM, (void) NULL);
		src->tok_buf = tmp;
		src->tok_bufsize *= 2;
	}
}

void	tok_buf_pop(t_source *src)
{
	src->tok_buf[src->tok_bufindex--] = '\0';
}
