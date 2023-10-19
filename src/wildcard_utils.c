/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:58:42 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 22:58:44 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcard.h"

/*
 * s should be malloc'd
 * */
int	wc_add(t_wildcard **origin, char *s)
{
	t_wildcard	*ret;
	t_wildcard	*i;

	if (!origin || !s)
		return (errno = ENODATA, -1);
	ret = malloc(sizeof(t_wildcard));
	if (!ret)
		return (errno = ENOMEM, -1);
	ret->is_done = ft_strchr(s, '*') == NULL;
	ret->s = s;
	ret->child = NULL;
	ret->next = NULL;
	ret->parent = NULL;
	if (!*origin)
		return (*origin = ret, 0);
	i = *origin;
	while (i->next)
		i = i->next;
	i->next = ret;
	ret->parent = i->parent;
	ret->child = i->child;
	return (0);
}

void	wc_clean(t_wildcard **i)
{
	t_wildcard	*j;

	if (!i || !*i)
		return ;
	if ((*i)->child)
		wc_clean(&(*i)->child);
	while (*i)
	{
		j = (*i)->next;
		free((*i)->s);
		free(*i);
		*i = j;
	}
}
