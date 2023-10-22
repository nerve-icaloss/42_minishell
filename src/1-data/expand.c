/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:46:48 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 16:47:03 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	expand_init(t_expand *expd, char *word)
{
	ft_memset(expd, 0, sizeof(*expd));
	expd->pstart = ft_strdup(word);
	if (!expd->pstart)
		return (errno = ENOMEM, -1);
	expd->p = expd->pstart;
	expd->in_double_quote = false;
	expd->expanded = false;
	return (0);
}
