/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:25:43 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/19 14:54:06 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *src, unsigned int n);

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	void	*to_return;

	if (!dest && !src)
		return (0);
	to_return = dest;
	while (dest - to_return < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
	}
	return (to_return);
}
