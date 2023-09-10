/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:35:02 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:54:35 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_strchr(char *s, int c);
char			*ft_strdup(char const *src);
char			*ft_substr(const char *s, unsigned int start, unsigned int len);
int				ft_strlen(char const *str);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);

char	*ft_substr(const char *s, unsigned int start, unsigned int len)
{
	char			*to_return;
	unsigned int	size;

	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(s + ft_strlen(s)));
	size = ft_strchr((char *)s + start, '\0') - ((char *)s + start);
	if (size > len)
		size = len;
	to_return = malloc(size + 1);
	if (to_return == NULL)
		return (NULL);
	ft_strlcpy(to_return, (char *)s + start, size + 1);
	return (to_return);
}
