/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:55:54 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 18:56:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_utils.h"
#include "libft/libft.h"

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

void	remove_quotes(t_node *args)
{

}
