/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:06:26 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 11:21:53 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	if (!s)
		return (0);
	p = (char *) s;
	while (*p && *p != (unsigned char)c)
		p++;
	if (*p != (unsigned char)c)
		return (0);
	return (p);
}
