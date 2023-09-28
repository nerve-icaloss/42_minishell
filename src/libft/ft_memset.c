/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:02:31 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/28 10:19:41 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, unsigned int n);

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (++i <= n)
		*(unsigned char *)(s + i - 1) = c;
	return (s);
}
