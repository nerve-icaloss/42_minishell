/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:59:10 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/18 15:40:34 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *big, const char *little, unsigned int len);

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	long	index;

	if (*little == '\0')
		return ((char *)big);
	index = 0;
	while (len > 0 && *big)
	{
		while (len-- > 0
			&& (*big == *(little + index) || *(little + index) == '\0'))
		{
			if (*(little + index) == '\0')
				return ((char *)big - index);
			index++;
			big++;
		}
		if (*(little + index) != '\0')
		{
			big -= index - 1;
			len += index;
			index = 0;
		}
		else
			return ((char *)big - index);
	}
	return (0);
}
