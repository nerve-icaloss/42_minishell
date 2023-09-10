/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:18 by hmelica           #+#    #+#             */
/*   Updated: 2023/07/21 14:03:33 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char			*found;
	static t_buffer	*b = NULL;
	t_buffer		*i;

	found = NULL;
	i = b;
	while (i && !found && fd >= 0)
	{
		found = ft_strchr(i->data + i->n, '\n');
		i = i->next;
	}
	if (found && fd >= 0)
		return (treatment(&b));
	i = buffer_new(&b);
	if (i && fd >= 0)
		i->size = read(fd, i->data, BUFFER_SIZE);
	while (i && fd >= 0 && i->size == BUFFER_SIZE && !ft_strchr(i->data, '\n'))
	{
		i = buffer_new(&i);
		i->size = read(fd, i->data, BUFFER_SIZE);
	}
	if (fd < 0 || !i || (i->size <= 0 && !*(b->data)))
		return ((char *)buffer_clean(&b));
	return (treatment(&b));
}

/*
 * len[0] is len to copy
 * len[1] is length of buffer
 * len[2] is length of blocks
 * */
char	*treatment(t_buffer **b)
{
	char		*found;
	char		*ret;
	int			len[3];
	t_buffer	*i;

	len[1] = 0;
	i = *b;
	len[2] = 0;
	found = ft_strchr(i->data + i->n, '\n');
	while (i->next && !found && ++len[2])
	{
		len[1] += i->size;
		i = i->next;
		found = ft_strchr(i->data, '\n');
	}
	if (!found)
		found = ft_strchr(i->data + i->n, '\0');
	len[0] = (len[1]) + found + 2 - ((*b)->n * (i != *b)) - (i->data
			+ i->n) - (*found == '\0');
	ret = malloc(sizeof(char) * len[0]);
	if (!ret)
		return ((char *)buffer_clean(b));
	ret += len[0];
	copypaste(b, &ret, len[0]);
	return (ret - len[0]);
}

void	copypaste(t_buffer **b, char **ret, int len)
{
	int			off;
	t_buffer	*j;

	j = *b;
	while (j && len > 0)
	{
		off = ft_strlcpy(*ret - len, j->data + j->n, len);
		if (off < len)
			j = buffer_remove(j);
		else
			j->n += off - 1;
		len -= off;
	}
	*b = j;
}
