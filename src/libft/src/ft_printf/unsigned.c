/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:39:28 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/24 11:07:57 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_u_number(unsigned int i, t_insert ins, int fd)
{
	char	c;
	int		ret;

	ret = 0;
	c = ' ';
	if (check_flag(ins.flags, '0'))
		c = '0';
	if (ins.min_width > 0 && !check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(fd, &c, 1);
	}
	while ((ins.prec-- > 0 || (ins.prec++ > 0)))
		write(fd, "0", 1);
	dec_rec(i, fd);
	return (ret);
}

int	main_u(va_list act, t_insert ins, int fd)
{
	int				ret;
	unsigned int	i;

	ret = 0;
	i = va_arg(act, unsigned int);
	ins.prec = (ins.prec - int_len(i)) * !check_flag(ins.flags, '0');
	ret += int_len(i) + (ins.prec * (ins.prec > 0));
	ins.min_width -= ret;
	ret += write_u_number(i, ins, fd);
	if (ins.min_width > 0 && check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(fd, " ", 1);
	}
	return (ret);
}
