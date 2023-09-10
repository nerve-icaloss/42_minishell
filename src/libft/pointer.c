/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:39:28 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/21 15:46:24 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Recursievly write down a pointer
*/
static int	pnt_rec(void *p)
{
	char	c;
	int		ret;

	ret = 1;
	c = "0123456789abcdef"[(unsigned long)p % 16];
	if ((unsigned long)p / 16)
		ret += pnt_rec((void *)((unsigned long)p / 16));
	write(1, &c, 1);
	return (ret);
}

/*
Check for interesting flags before writing pointer
*/
static int	write_pointer(void *p, t_insert ins)
{
	int	ret;

	ret = 0;
	ins.min_width -= 2 + hex_len((unsigned long) p);
	if (ins.min_width > 0 && !check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, " ", 1);
	}
	ret += pnt_rec(p);
	if (ins.min_width > 0 && check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, " ", 1);
	}
	return (ret);
}

/*
Writes a pointer argument
*/
int	main_p(va_list act, t_insert ins)
{
	void	*p;

	p = va_arg(act, void *);
	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (check_flag(ins.flags, ' '))
		write(1, " ", 1);
	else if (check_flag(ins.flags, '+'))
		write(1, "+", 1);
	write(1, "0x", 2);
	return (2 + write_pointer(p, ins) + (check_flag(ins.flags, ' ')
			|| check_flag(ins.flags, '+')));
}
