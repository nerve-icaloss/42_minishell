/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:41:38 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 22:41:40 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcard.h"

int	wc_rec_expand(t_wildcard *wc);

char	*insert_name(t_wildcard *wc, char name[256])
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin2(wc->path, name, 0, 0);
	ret = ft_strjoin2(ret, wc->following, 1, 0);
	return (ret);
}

int	wc_run_child(t_wildcard *wc)
{
	t_wildcard	*child;

	ft_dprintf(2, "inside launcher\n");
	if (!wc || !wc->child)
		return (0);
	ft_dprintf(2, "inside launcher 2\n");
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
		return (ft_dprintf(2, "DO NOT EXPAND %s\n", wc->s), 0);
	ft_dprintf(2, "RUNNING EXPAND %s : (%s)/(%s)*(%s)/(%s)\n", wc->s, wc->path, wc->glob_prev, wc->glob_next, wc->following);
	dir = opendir(wc->path);
	if (!dir)
		return (errno = ENOENT, -1);
	elem = readdir(dir);
	while (elem)
	{
		if (ft_memcmp(elem->d_name, "..", 3) == 0 || ft_memcmp(elem->d_name,
				".", 2) == 0 || !glob_name(elem->d_name, wc->glob_prev,
				wc->glob_next) || (wc->following && *wc->following
				&& !is_dir(wc, elem)))
		{
			ft_dprintf(2, "Not recorded '%s' (%d)'\n", elem->d_name, (wc->following && *wc->following && !is_dir(wc, elem)));
			elem = readdir(dir);
			continue ;
		}
		path = insert_name(wc, elem->d_name);
		ft_dprintf(2, "Will be recorded '%s' (%d)(%s) : '%c'\n", path, is_dir(wc, elem), wc->following, *wc->following);
		if (wc_add(&wc->child, path))
			return (closedir(dir), free(path), errno = ENOMEM, -1);
		elem = readdir(dir);
	}
	(void) closedir(dir);
	return (wc_run_child(wc));
}

/*
 * s should be one single path, with only alphanum and / and *
 * s will not be freed inside this function
 * */
char	*generate_wildcard(char *s)
{
	char		*string;
	t_wildcard	*wc;

	if (!s)
		return (errno = ENODATA, NULL);
	wc = NULL;
	string = ft_strdup(s);
	if (wc_add(&wc, string))
		return (NULL);
	if (wc_rec_expand(wc))
		return (wc_clean(&wc), NULL);
	string = wc_to_str(wc);
	wc_clean(&wc);
	return (string);
}
