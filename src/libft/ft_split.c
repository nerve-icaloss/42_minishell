/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:30:21 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:55:38 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		**ft_split(const char *str, char c);
char		*ft_substr(const char *s, unsigned int start, unsigned int len);
static char	*get_next(const char **str, char sep);
static int	count_words(const char *str, char sep);

/*
count how many words
*/
static int	count_words(const char *str, char sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == sep && *str)
			str++;
		if (*str)
			count++;
		while (*str != sep && *str)
			str++;
	}
	return (count);
}

/*
return the length until next space or NUL
*/
static char	*get_next(const char **str, char sep)
{
	char	*word;
	int		len;

	len = 0;
	while (**str != sep && **str)
	{
		len++;
		(*str)++;
	}
	word = ft_substr(*str - len, 0, len);
	return (word);
}

/*
split the single string input into a string for each word
*/
char	**ft_split(const char *str, char c)
{
	char	**tab;
	char	**to_return;
	int		len;

	if (!str)
		return (NULL);
	len = count_words(str, c);
	to_return = malloc(sizeof(char *) * (len + 1));
	if (!to_return)
		return (NULL);
	tab = to_return;
	tab[len] = NULL;
	while (tab - to_return < len)
	{
		while (*str == c && *str)
			str++;
		*tab = get_next(&str, c);
		if (!*tab)
			return (NULL);
		tab++;
	}
	return (to_return);
}
