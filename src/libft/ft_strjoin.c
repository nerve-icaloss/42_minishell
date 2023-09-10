/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:38:38 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:55:23 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(char const *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*to_return;
	unsigned int	i;
	unsigned int	len;
	unsigned int	tlen;

	tlen = ft_strlen(s1) + ft_strlen(s2);
	to_return = malloc(sizeof(char) * (tlen + 1));
	if (to_return == NULL)
		return (NULL);
	to_return[tlen] = '\0';
	i = 0;
	len = ft_strlen(s1);
	while (i++ < len)
		to_return[i - 1] = s1[i - 1];
	i = 0;
	while (i++ + len < tlen)
		to_return[len + i - 1] = s2[i - 1];
	return (to_return);
}
