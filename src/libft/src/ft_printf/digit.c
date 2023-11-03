/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:39:28 by hmelica           #+#    #+#             */
/*   Updated: 2023/11/03 13:49:26 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Recursiviely write an int
*/
int	dec_rec(unsigned int i, int fd)
{
	char	c;

	c = (i % 10) + '0';
	if (i / 10)
		if (dec_rec(i / 10, fd) < 0)
			return (-1);
	if (write(fd, &c, 1) < 0)
		return (-1);
	return (1);
}

/*
Return len of an unsigned int
*/
int	int_len(unsigned int i)
{
	int		ret;

	ret = 1;
	if (i / 10)
		ret += int_len(i / 10);
	return (ret);
}

/*
First usual function to write down number (and prev width stuff)
*/
static int	write_number(unsigned int ui, t_insert ins, int i, int fd)
{
	char	c;
	int		ret;

	ret = 0;
	c = ' ' * (check_flag(ins.flags, '0') == 0) + '0' * (check_flag(ins.flags,
				'0') != 0);
	if (i < 0 && (check_flag(ins.flags, '0')) && write(fd, "-", 1) < 0)
		return (-1);
	if (ins.min_width > 0 && !check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			if (write(fd, &c, 1) < 0)
				return (-1);
	}
	if (i < 0 && (!check_flag(ins.flags, '0') || ins.prec < 0) && write(fd, "-",
			1) < 0)
		return (-1);
	if (i >= 0 && check_flag(ins.flags, ' ') && write(fd, " ", 1) < 0)
		return (-1);
	else if (i >= 0 && check_flag(ins.flags, '+') && write(fd, "+", 1) < 0)
		return (-1);
	while ((ins.prec-- > 0 || (ins.prec++ > 0)) && write(fd, "0", 1) < 0)
		return (-1);
	return (dec_rec(ui, fd) * ret);
}

/*
Function to write a digit :
run write_number and next width stuff
*/
int	main_d(va_list act, t_insert ins, int fd)
{
	int				ret;
	int				i;
	unsigned int	ui;

	ret = 0;
	i = va_arg(act, int);
	ui = i;
	if (i < 0)
		ui = i * -1;
	ins.prec = (ins.prec - int_len(ui)) * !check_flag(ins.flags, '0');
	ret += int_len(ui) + (i < 0 || check_flag(ins.flags, ' ')
			|| check_flag(ins.flags, '+')) + (ins.prec * (ins.prec > 0));
	ins.min_width -= ret;
	ret += write_number(ui, ins, i, fd);
	if (ins.min_width > 0 && check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			if (write(fd, " ", 1) < 0)
				return (-1);
	}
	return (ret);
}
