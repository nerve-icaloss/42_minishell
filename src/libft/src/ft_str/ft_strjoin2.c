/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:45:12 by nserve            #+#    #+#             */
/*   Updated: 2023/02/09 10:46:49 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*ret;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	ret = malloc(sizeof(*ret) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		ret[i++] = *(s1++);
	while (s2 && *s2)
		ret[i++] = *(s2++);
	ret[i] = '\0';
	if (s1 && free_s1)
		free(s1);
	if (s2 && free_s2)
		free(s2);
	return (ret);
}
