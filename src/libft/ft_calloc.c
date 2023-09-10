/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:53:49 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/13 19:57:39 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(unsigned int nmemb, unsigned int size);

void	*ft_calloc(unsigned int nmemb, unsigned int size)
{
	void				*to_return;
	unsigned long long	n;

	if ((unsigned long long) nmemb * size > (unsigned long long) 2 * 2147483648)
		return (NULL);
	to_return = malloc(nmemb * size);
	if (to_return == NULL)
		return (NULL);
	n = 0;
	while (n++ < nmemb * size)
		*(unsigned char *)(to_return + n - 1) = 0;
	return (to_return);
}
