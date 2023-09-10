/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:29:44 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/21 15:45:01 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
read argument at place
*/
static int	read_arg_at(int n, va_list act, va_list ori)
{
	if (n == 0)
		return (va_arg(act, int));
	while (--n > 0)
		va_arg(ori, int);
	return (va_arg(ori, int));
}

/*
Get int value of an argument (including pointing to others args)
return 0 if error (or when 0 read, that acts as a default behavior)
*/
static int	get_int_value(const char **format, va_list act, va_list ori)
{
	int	ret;

	ret = 0;
	if (is_digit(**format) || **format == '-')
		return (read_following_int(format));
	else if (**format != '*')
		return (0);
	(*format)++;
	if (is_digit(**format))
	{
		ret = read_following_int(format);
		if (**format != '$')
			return (0);
		(*format)++;
	}
	return (read_arg_at(ret, act, ori));
}

/*
Handle the min width input, *format start at the possible number
*/
int	get_min_width(const char **format, int *flags, va_list act, va_list ori)
{
	int	ret;

	if (!is_digit(**format) && **format != '*')
		return (0);
	ret = get_int_value(format, act, ori);
	if (ret < 0)
	{
		if (!check_flag(*flags, '-'))
			*flags += set_flag('-');
		ret *= -1;
	}
	return (ret);
}

/*
Handle the precision input, *format start at the '.'
*/
int	precision(const char **format, va_list act, va_list ori)
{
	int	ret;

	if (!is_digit(*(++(*format))) && **format != '*')
		return (0);
	ret = get_int_value(format, act, ori);
	if (ret < 0)
		return (-1);
	return (ret);
}

/*
display string s and handle min_width
force len = 0 if not forced
*/
int	display(char *s, t_insert ins, int force_len)
{
	int	ret;
	int	len;

	ret = 0;
	len = force_len;
	if (!force_len)
		len = ft_strlen(s);
	ins.min_width -= len;
	if (ins.min_width > 0 && !check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, " ", 1);
	}
	write(1, s, len);
	ret += len;
	if (ins.min_width > 0 && check_flag(ins.flags, '-'))
	{
		while (ins.min_width-- > 0 && ++ret)
			write(1, " ", 1);
	}
	return (ret);
}
