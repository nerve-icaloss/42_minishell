/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:40:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/24 19:36:54 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handler(va_list act, t_insert ins, int fd);
int	separation(const char **format, int ret[2],
				va_list act, va_list ori);

int	ft_dprintf(int fd, const char *format, ...)
{
	int				ret[2];
	va_list			args;
	va_list			origin;
	va_list			act;

	if (fd < 0)
		return (write(2, "Incorrect fd\n", 13));
	va_start(act, format);
	va_copy(origin, act);
	ret[0] = fd;
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
			write(fd, format, 1);
		format++;
	}
	va_end(act);
	va_end(origin);
	return (ret[1]);
}
