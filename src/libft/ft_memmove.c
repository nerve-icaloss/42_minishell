/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:01:19 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:53:37 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, unsigned int n);

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	unsigned int	i;

	if (src - dest == 0)
		return (dest);
	i = 0;
	if (src - dest > 0)
	{
		while (i++ < n)
			*(unsigned char *)(dest + i - 1) = *(unsigned char *)(src + i - 1);
	}
	else
	{
		while (i++ < n)
			*(unsigned char *)(dest + n - i) = *(unsigned char *)(src + n - i);
	}
	return (dest);
}
