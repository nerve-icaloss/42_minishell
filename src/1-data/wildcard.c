/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:58:42 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 17:03:45 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	wc_init_prev(t_wildcard *wc, char *s)
{
	char	*i;
	char	*j;

	i = s;
	j = ft_strchr(i, '/');
	while (j && j < wc->wc)
	{
		i = j;
		j = ft_strchr(i + 1, '/');
	}
	if (i != s)
	{
		wc->path = ft_substr(s, 0, i + 1 - s);
		wc->glob_prev = ft_substr(i + 1, 0, wc->wc - i - 1);
	}
	else
	{
		wc->path = ft_strdup("./");
		wc->glob_prev = ft_substr(s, 0, wc->wc - s);
	}
	if (!wc->path || !wc->glob_prev)
		return (errno = ENOMEM, -1);
	return (0);
}

static int	wc_init_next(t_wildcard *wc)
{
	char	*i;
	char	*j;

	if (!*wc->wc)
		return (0);
	i = wc->wc + 1;
	j = ft_strchr(i, '/');
	if (j && j != i)
	{
		wc->glob_next = ft_substr(i, 0, j - i);
		wc->following = ft_strdup(j);
	}
	else if (j == i)
	{
		wc->glob_next = ft_strdup("");
		wc->following = ft_strdup(i);
	}
	else
	{
		wc->following = ft_strdup("");
		wc->glob_next = ft_strdup(i);
	}
	if (!wc->following || !wc->glob_next)
		return (errno = ENOMEM, -1);
	return (0);
}

int	wc_init(t_wildcard *wc, char *s)
{
	if (!wc || !s)
		return (-1);
	wc->s = s;
	wc->wc = ft_strchr(s, '*');
	if (!wc->wc)
		return (0);
	if (wc_init_prev(wc, s))
		return (-1);
	if (wc_init_next(wc))
		return (-1);
	return (0);
}

/*
 * s should be malloc'd
 * s is free'd in case of problem
 * */
int	wc_add(t_wildcard **origin, char *s)
{
	t_wildcard	*ret;
	t_wildcard	*i;

	if (!s)
		return (errno = ENODATA, -1);
	ret = malloc(sizeof(t_wildcard));
	if (!ret)
		return (free(s), errno = ENOMEM, -1);
	ft_bzero(ret, sizeof(t_wildcard));
	if (wc_init(ret, s))
		return (errno = ENOMEM, wc_clean(&ret), -1);
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
		if ((*i)->s)
			free((*i)->s);
		if ((*i)->path)
			free((*i)->path);
		if ((*i)->glob_next)
			free((*i)->glob_next);
		if ((*i)->glob_prev)
			free((*i)->glob_prev);
		if ((*i)->following)
			free((*i)->following);
		free(*i);
		*i = j;
	}
}
