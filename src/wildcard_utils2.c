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

char	*wc_to_str(t_wildcard *wc)
{
	char		*s;
	t_wildcard	*child;

	if (!wc)
		return (NULL);
	s = NULL;
	child = wc->child;
	while (child)
	{
		s = wc_to_str(child);
		child = child->next;
	}
	child = wc;
	while (child && !child->wc)
	{
		if (s)
			s = ft_strjoin2(s, " ", 1, 0);
		s = ft_strjoin2(s, wc->s, 1, 0);
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
			return (0);
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
			return (free(to_find), 0);
		len[1] = ft_strlen(to_find);
		i = found - name + len[1];
		next += len[1] + (next_star != NULL);
		free(to_find);
	}
	if (name[i] && *(next - 1) == '*')
		return (1);
	return (name[i] == '\0');
}

/*
 * return 1 if match
 * */
int	glob_name(char name[256], char *prev, char *next)
{
	size_t	len;

	len = 0;
	if (prev && *prev)
	{
		len = ft_strlen(prev);
		if (ft_strncmp(name, prev, len))
			return (0);
	}
	if (next && *next)
		if (!glob_name_next(name, next, len))
			return (0);
	return (1);
}
