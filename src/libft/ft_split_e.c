/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:30:21 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:56:06 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		**ft_split_e(const char *str, char c, char *b_set, char *e_set);
char		*ft_substr(const char *s, unsigned int start, unsigned int len);
static char	*get_next(const char **str, char sep, char *b_set, char *e_set);
static int	count_words(const char *str, char sep, char *b_set, char *e_set);

/*
count how many words
*/
static int	count_words(const char *str, char sep, char *b_set, char *e_set)
{
	int	count;
	int	index;

	count = 0;
	while (*str)
	{
		while (*str == sep && *str)
			str++;
		if (*str)
			count++;
		if (*str && ft_strchr(b_set, *str))
		{
			index = ft_strchr(b_set, *str) - b_set;
			while (*(++str) && *str != e_set[index])
				str++;
		}
		while (*str != sep && *str)
			str++;
	}
	return (count);
}

/*
return the length until next space or NULL
*/
static char	*get_next(const char **str, char sep, char *b_set, char *e_set)
{
	char	*word;
	int		index;
	int		len;
	int		offset;

	len = 0;
	offset = 0;
	if (**str && ft_strchr(b_set, **str))
	{
		offset = 1;
		index = ft_strchr(b_set, **str) - b_set;
		while (*(++(*str)) && **str != e_set[index])
		{
			len++;
		}
		if (!**str)
			offset = 0;
	}
	while (**str != sep && **str)
	{
		len++;
		(*str)++;
	}
	word = ft_substr(*str - len, 0, len - offset);
	return (word);
}

/*
split the single string input into a string for each word
*/
char	**ft_split_e(const char *str, char c, char *b_set, char *e_set)
{
	char	**tab;
	char	**to_return;
	int		len;

	if (!str)
		return (NULL);
	len = count_words(str, c, b_set, e_set);
	to_return = malloc(sizeof(char *) * (len + 1));
	if (!to_return)
		return (NULL);
	tab = to_return;
	tab[len] = NULL;
	while (tab - to_return < len)
	{
		while (*str == c && *str)
			str++;
		*tab = get_next(&str, c, b_set, e_set);
		if (!*tab)
			return (NULL);
		tab++;
	}
	return (to_return);
}
