/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:41:38 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 22:41:40 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcard.h"

int	wc_rec_expand(t_wildcard *wc)
{
	char		*path;
	DIR			*dir;
	t_dirent	*elem;

	if (!wc->wc)
		return (0);
	if (wc->wc - wc->s == 0)
		path = ft_strdup("./");
	else
		path = ft_substr(wc->s, 0, wc->wc - wc->s);
	if (!path)
		return (errno = ENODATA, -1);
	(void) dir;
	(void) elem;
	return (0);
}

/*
 * s should be one single path
 * s will not be freed inside this function
 * */
char	*generate_wildcard(char *s, t_myenv *env)
{
	char		*string;
	t_wildcard	*wc;

	if (!s || !env)
		return (errno = ENODATA, NULL);
	wc = NULL;
	string = ft_strdup(s);
	if (wc_add(&wc, string))
		return (free(string), NULL);
	if (wc_rec_expand(wc))
		return (wc_clean(&wc), NULL);
	(void) env;
	return (0);
}
