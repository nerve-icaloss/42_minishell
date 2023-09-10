/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:22:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:53:18 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char				*ft_strchr(char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char *s, unsigned int start, unsigned int len);
static unsigned int	get_new_len(char const *s1, char const *set);

static unsigned int	get_new_len(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	new_len;
	unsigned int	start;

	start = 0;
	new_len = 0;
	while (*(s1 + start) && ft_strchr((char *)set, *(s1 + start)) != 0)
		start++;
	i = start;
	start = 0;
	while (*(s1 + i))
	{
		new_len += start;
		i -= new_len;
		while (*(s1 + i + new_len)
			&& ft_strchr((char *)set, *(s1 + i + new_len)) == 0)
			new_len++;
		i += new_len;
		start = 0;
		while (*(s1 + i + start)
			&& ft_strchr((char *)set, *(s1 + i + start)) != 0)
			start++;
		i += start;
	}
	return (new_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*to_return;
	unsigned int	new_len;
	unsigned int	start;

	new_len = get_new_len(s1, set);
	start = 0;
	while (*(s1 + start) && ft_strchr((char *)set, *(s1 + start)) != 0)
		start++;
	to_return = ft_substr((char *)s1, start, new_len);
	return (to_return);
}
