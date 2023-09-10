/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:00:47 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:55:16 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char					*ft_itoa(int n);
static unsigned long	ten_pow(unsigned int n);
static void				req(unsigned int n, char *tab, int i);

static void	req(unsigned int n, char *tab, int i)
{
	if (n >= 10)
		req(n / 10, tab, i - 1);
	tab[i] = (n % 10) + '0';
}

static unsigned long	ten_pow(unsigned int n)
{
	if (n == 0)
		return (1);
	return (ten_pow(n - 1) * 10);
}

char	*ft_itoa(int n)
{
	char			*to_return;
	int				len;
	int				negative;
	unsigned int	nb;

	len = 1;
	negative = 0;
	nb = n;
	if (n < 0)
	{
		negative = 1;
		nb = -n;
	}
	while (nb / ten_pow(len) > 0)
		len++;
	to_return = malloc(len + 1 + negative);
	if (to_return == NULL)
		return (NULL);
	to_return[len + negative] = '\0';
	if (negative)
		to_return[0] = '-';
	len += negative;
	req(nb, to_return, len - 1);
	return (to_return);
}
