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

int	glob_name(char name[256], char *prev, char *next)
{
	size_t	len;
	char	*s;

	if (prev && *prev)
	{
		len = ft_strlen(prev);
		if (ft_strncmp(name, prev, len))
			return (0);
	}
	if (next && *next)
	{
		s = ft_strnstr(name, next, ft_strlen(name));
		len = ft_strlen(next);
		if (!s || ft_strlen(s) != len || ft_strncmp(s, next, len))
			return (0);
	}
	return (1);
}

int	wc_rec_expand(t_wildcard *wc)
{
	char		*path;
	DIR			*dir;
	t_dirent	*elem;

	if (!wc->wc)
		return (0);
	dir = opendir(wc->path);
	if (!dir)
		return (errno = ENOENT, -1);
	elem = readdir(dir);
	while (elem)
	{
		if (!glob_name(elem->d_name, wc->glob_prev, wc->glob_next))
			continue ;
		path = ft_strjoin(wc->path, elem->d_name);
	}
	return (0);
}

/*
 * s should be one single path
 * s will not be freed inside this function
 * */
char	*generate_wildcard(char *s, t_myenv *env)
{
	char		*string;
	t_wildcard	*wc;

	if (!s || !env)
		return (errno = ENODATA, NULL);
	wc = NULL;
	string = ft_strdup(s);
	if (wc_add(&wc, string))
		return (free(string), NULL);
	if (wc_rec_expand(wc))
		return (wc_clean(&wc), NULL);
	(void) env;
	return (0);
}
