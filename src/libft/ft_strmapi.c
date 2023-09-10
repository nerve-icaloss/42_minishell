/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:01:02 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:54:43 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strdup(char const *src);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strlen(char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*to_return;
	unsigned int	i;
	unsigned int	len;

	if (!f)
		return ((char *)s);
	to_return = ft_strdup(s);
	if (!to_return)
		return (0);
	len = ft_strlen(to_return);
	i = 0;
	while (i++ < len)
		to_return[i - 1] = (*f)(i - 1, s[i - 1]);
	return (to_return);
}
