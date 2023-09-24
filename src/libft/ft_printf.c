/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:53:02 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/24 11:04:47 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handler(va_list act, t_insert ins, int fd);
static int	separation(const char **format, int ret[2],
				va_list act, va_list ori);

/*
main func
*/
int	ft_printf(const char *format, ...)
{
	int				ret[2];
	va_list			args;
	va_list			origin;
	va_list			act;

	va_start(act, format);
	va_copy(origin, act);
	ret[0] = 1;
	ret[1] = 0;
	while (format && *format)
	{
		if (*format == '%')
		{
			va_copy(args, origin);
			separation(&format, ret, act, args);
			va_end(args);
		}
		else if (++ret[1])
			write(ret[0], format, 1);
		format++;
	}
	va_end(act);
	va_end(origin);
	return (ret[1]);
}

/*
FLAGS : every binary 1 tells that the flag exists
1   '-' : left adjusted
2   '0' : zero padded
4   '#' : alternate form (???)
8   ' ' : blank before if positive
16  '+' : + before if positive

this func is handeling an insert, *format pointing at '%'
at the end, format is pointing at the csp
*/
static int	separation(const char **format, int ret[2],
	va_list act, va_list ori)
{
	t_insert	ins;
	const char	*origin;

	origin = *format;
	ins.flags = 0;
	ins.min_width = 0;
	ins.prec = -1;
	while (++(*format) && is_flag(**format))
		ins.flags += set_flag(**format);
	ins.min_width = get_min_width(format, &(ins.flags), act, ori);
	if (**format == '.')
		ins.prec = precision(format, act, ori);
	compile_flags(&ins);
	if (!is_csp(**format))
	{
		ret[1]++;
		*format = origin;
		write(ret[0], "%", 1);
		return (0);
	}
	ins.type = **format;
	ret[1] += handler(act, ins, ret[0]);
	return (*ret);
}

/*
Launch different functions depending on the csp
Return number of char printed
*/
static int	handler(va_list act, t_insert ins, int fd)
{
	if (ins.type == 'c')
		return (main_c(act, ins, fd));
	if (ins.type == 's')
		return (main_s(act, ins, fd));
	if (ins.type == 'p')
		return (main_p(act, ins, fd));
	if (ins.type == 'd' || ins.type == 'i')
		return (main_d(act, ins, fd));
	if (ins.type == 'u')
		return (main_u(act, ins, fd));
	if (ins.type == 'x')
		return (main_x(act, ins, "0123456789abcdefx", fd));
	if (ins.type == 'X')
		return (main_x(act, ins, "0123456789ABCDEFX", fd));
	if (ins.type == '%')
	{
		write(fd, "%", 1);
		return (1);
	}
	return (0);
}
