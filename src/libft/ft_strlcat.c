/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:39:35 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:55:43 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	long			ssize;
	unsigned int	length;

	if (size == 0)
		return (ft_strlen(src));
	ssize = size;
	length = ft_strlen(dest) + ft_strlen(src);
	if (ssize < ft_strlen(dest))
		length = ssize + ft_strlen(src);
	ssize -= ft_strlen(dest);
	if (ssize < 1)
		return (length);
	while (*dest)
		dest++;
	while (*src && --ssize > 0)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
	return (length);
}
