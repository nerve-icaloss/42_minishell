/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:04:48 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/19 14:22:05 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	i;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	i = n;
	if (i >= 10)
		ft_putnbr_fd(i / 10, fd);
	c = (i % 10) + '0';
	write(fd, &c, 1);
}
