/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:39:28 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/21 15:46:48 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_rec(unsigned int i, char *tab)
{
	int		ret;

	ret = 1;
	if (i / 16)
		ret += hex_rec(i / 16, tab);
	write(1, tab + (i % 16), 1);
	return (ret);
}

static int	write_x_number(unsigned int i, t_insert ins, char *tab)
{
	char	c;
	int		ret;

	ret = 0;
	c = ' ';
	if (i != 0 && check_flag(ins.flags, '#'))
	{
		ret += 2;
		write(1, "0", 1);
		write(1, tab + 16, 1);
	}
	if (check_flag(ins.flags, '0'))
		c = '0';
	if (ins.min_width > 0 && !check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, &c, 1);
	}
	while ((ins.prec-- > 0 || (ins.prec++ > 0)))
		write(1, "0", 1);
	hex_rec(i, tab);
	return (ret);
}

int	hex_len(unsigned long i)
{
	int		ret;

	ret = 1;
	if (i / 16)
		ret += hex_len(i / 16);
	return (ret);
}

int	main_x(va_list act, t_insert ins, char *tab)
{
	int				ret;
	unsigned int	i;

	ret = 0;
	i = va_arg(act, unsigned int);
	ins.prec = (ins.prec - hex_len(i)) * !check_flag(ins.flags, '0');
	ret += hex_len(i) + (ins.prec * (ins.prec > 0));
	ins.min_width -= ret;
	ret += write_x_number(i, ins, tab);
	if (ins.min_width > 0 && check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, " ", 1);
	}
	return (ret);
}
