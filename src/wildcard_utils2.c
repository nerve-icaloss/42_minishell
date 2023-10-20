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
	if (child && !child->wc )
	{
		if (s)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, child->s, 1, 0);
		child = child->next;
	}
	return (s);
}

int	glob_name_next(char name[256], char *next, size_t i)
{
	char	*next_star;
	char	*to_find;
	char	*found;
	size_t	len[2];

	len[0] = ft_strlen(name);
	to_find = NULL;
	while (name[i] && *next)
	{
		next_star = ft_strchr(next, '*');
		if (next_star)
			to_find = ft_substr(next, 0, next_star - next);
		else
			to_find = ft_strdup(next);
		if (!to_find)
			return (ft_dprintf(2, "Not valid 2.1\n"), 0);
		found = ft_strnstr(name + i, to_find, len[0]);
		if (!next_star && found)
		{
			next_star = ft_strnstr(found, to_find, ft_strlen(found));
			while (next_star)
			{
				found = next_star + 1;
				next_star = ft_strnstr(found, to_find, ft_strlen(found));
			}
		}
		if (!found)
			return (ft_dprintf(2, "Not valid 2.2\n"), free(to_find), 0);
		len[1] = ft_strlen(to_find);
		i = found - name + len[1];
		next += len[1] + (next_star != NULL);
		free(to_find);
	}
	if ((i > len[0]) && *(next - 1) == '*')
		return (1);
	return (ft_dprintf(2, "Valid Maybe ? 2.3 (%d/%d)\n", i, len[0]), (i > len[0]));
}

/*
 * return 1 if match
 * */
int	glob_name(char name[256], char *prev, char *next)
{
	size_t	len;

	ft_dprintf(2, "globbing : (%s)%s(%s)\n", prev, name, next);
	len = 0;
	if (prev && *prev)
	{
		len = ft_strlen(prev);
		if (ft_strncmp(name, prev, len))
			return (ft_dprintf(2, "Not valid 1\n"), 0);
	}
	if (next && *next)
		if (!glob_name_next(name, next, len))
			return (ft_dprintf(2, "Not valid 2 (%d)\n", len), 0);
	ft_dprintf(2, "Valid\n");
	return (1);
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
	ft_dprintf(2, "is dir %s ?\n", path);
	if (stat(path, &stbuff))
		return (free(path), 0);
	free(path);
	return (S_ISDIR(stbuff.st_mode));
}
