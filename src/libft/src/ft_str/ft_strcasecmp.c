/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:26:05 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 14:36:27 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while ((unsigned char)*s1 == (unsigned char)*s2)
	{
		s1++;
		s2++;
	}
	return ((ft_tolower(*s1) + ft_isupper(*s1)) - (ft_tolower(*s2) + ft_isupper(*s2)));
}
