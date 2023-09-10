/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:21:59 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/12 15:32:22 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, unsigned int n);

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n-- > 1 && *(unsigned char *)(s + i) != (unsigned char)c)
		i++;
	if (*(unsigned char *)(s + i) == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}
