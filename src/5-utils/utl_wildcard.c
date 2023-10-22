/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:00 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 17:03:29 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*insert_name(t_wildcard *wc, char name[256])
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin2(wc->path, name, 0, 0);
	ret = ft_strjoin2(ret, wc->following, 1, 0);
	return (ret);
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

int	wc_run_child(t_wildcard *wc)
{
	t_wildcard	*child;

	if (!wc || !wc->child)
		return (0);
	child = wc->child;
	while (child)
	{
		if (wc_rec_expand(child))
			return (-1);
		child = child->next;
	}
	return (0);
}

int	wc_rec_expand(t_wildcard *wc)
{
	char		*path;
	DIR			*dir;
	t_dirent	*elem;

	if (!wc || !wc->wc)
		return (0);
	dir = opendir(wc->path);
	if (!dir)
		return (errno = ENOENT, -1);
	elem = readdir(dir);
	while (elem)
	{
		if (wc_pregnant(wc, elem))
		{
			elem = readdir(dir);
			continue ;
		}
		path = insert_name(wc, elem->d_name);
		if (wc_add(&wc->child, path))
			return (closedir(dir), free(path), errno = ENOMEM, -1);
		elem = readdir(dir);
	}
	(void) closedir(dir);
	return (wc_run_child(wc));
}
