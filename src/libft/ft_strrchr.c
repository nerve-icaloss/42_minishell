/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:06:26 by hmelica           #+#    #+#             */
/*   Updated: 2022/11/12 19:18:22 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(char *s, int c);

char	*ft_strrchr(char *s, int c)
{
	char	*to_return;

	to_return = 0;
	while (*s)
	{
		if (*s == (char)c)
			to_return = s;
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (to_return);
}
