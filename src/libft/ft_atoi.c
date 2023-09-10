/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:21:48 by hmelica           #+#    #+#             */
/*   Updated: 2023/05/30 13:50:19 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi(const char *str);
static int	ft_isspace(char c);

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	signe;
	int	written;

	result = 0;
	written = 0;
	signe = 1;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
		{
			result *= 10;
			result += *str - '0';
			written = 2;
		}
		else if ((*str == '+' || *str == '-') && written < 2)
		{
			signe *= 1 - (2 * (*str / '-'));
			written = 2;
		}
		else if (!ft_isspace(*str) || written)
			break ;
		str++;
	}
	return (result * signe);
}
