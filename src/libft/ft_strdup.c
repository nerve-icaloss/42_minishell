/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:24:27 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:56:35 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char const *src);
int		ft_strlen(char *str);

char	*ft_strdup(char const *src)
{
	char	*to_return;
	int		len;

	len = 1;
	while (src[len - 1])
		len++;
	to_return = malloc(sizeof(char) * len);
	if (to_return == NULL)
		return (NULL);
	to_return[len - 1] = '\0';
	while (len-- > 0)
		to_return[len] = src[len];
	return (to_return);
}
