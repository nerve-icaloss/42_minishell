/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:50:01 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 11:37:49 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	ret;

	ret = 0;
	while (*src && *src != EOF && size-- && ++ret)
		*(dest++) = *(src++);
	if ((int)size <= 0)
	{
		*(dest - 1) = '\0';
		return (ret);
	}
	*dest = '\0';
	return (ret);
}
