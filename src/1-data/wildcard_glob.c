/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_glob.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:03:33 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 16:57:46 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	set_next_star(char **next_star, char **next, char **to_find)
{
	*next_star = ft_strchr(*next, '*');
	if (*next_star)
		*to_find = ft_substr(*next, 0, *next_star - *next);
	else
		*to_find = ft_strdup(*next);
	if (!*to_find)
		return (0);
	return (1);
}

void	find_last(char **next_star, char **found, char **to_find)
{
	size_t	len;

	len = ft_strlen(*found);
	*next_star = ft_strnstr(*found, *to_find, ft_strlen(*found));
	while (*next_star && len)
	{
		*found = *next_star + 1;
		len = ft_strlen(*found);
		*next_star = ft_strnstr(*found, *to_find, len);
	}
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
		if (!set_next_star(&next_star, &next, &to_find))
			return (0);
		found = ft_strnstr(name + i, to_find, len[0]);
		if (!next_star && found)
			find_last(&next_star, &found, &to_find);
		if (!found)
			return (free(to_find), 0);
		len[1] = ft_strlen(to_find);
		i = found - name + len[1];
		next += len[1] + (next_star != NULL);
		free(to_find);
	}
	//if ((i > len[0]) && *(next - 1) == '*')
	//	return (1);
	//return (i > len[0]);
	if (name[i] && *(next - 1) == '*')
		return (1);
	ft_dprintf(2, ">> '%s'[%d] : (%c)\n", name, i, name[i]);
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
