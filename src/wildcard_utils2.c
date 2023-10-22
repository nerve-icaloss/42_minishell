/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:00 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/20 11:11:03 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcard.h"
#include <sys/wait.h>

char	*wc_to_str(t_wildcard *wc)
{
	char		*s;
	char		*a;
	t_wildcard	*child;

	if (!wc)
		return (NULL);
	s = NULL;
	child = wc->child;
	while (child)
	{
		a = wc_to_str(child);
		if (s && a)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, a, 1, 0);
		child = child->next;
	}
	child = wc;
	if (child && !child->wc)
	{
		if (s)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, child->s, 1, 0);
		child = child->next;
	}
	return (s);
}

/*
 * returns 1 if elem is is dir
 * */
int	is_dir(t_wildcard *wc, t_dirent *elem)
{
	char	*path;
	t_stat	stbuff;

	if (!elem || !wc)
		return (0);
	path = ft_strjoin2(wc->path, elem->d_name, 0, 0);
	if (stat(path, &stbuff))
		return (free(path), 0);
	free(path);
	return (S_ISDIR(stbuff.st_mode));
}

int	wc_pregnant(t_wildcard *wc, t_dirent *elem)
{
	return (ft_memcmp(elem->d_name, "..", 3) == 0 || ft_memcmp(elem->d_name,
			".", 2) == 0 || !glob_name(elem->d_name, wc->glob_prev,
			wc->glob_next) || (wc->following && *wc->following
			&& !is_dir(wc, elem)));
}
