/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:51 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:54:24 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, unsigned int n);
void	ft_bzero(void *s, unsigned int n);

void	ft_bzero(void *s, unsigned int n)
{
	ft_memset(s, '\0', n);
}
