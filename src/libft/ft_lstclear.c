/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:35:47 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:53:31 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *));

/*
Le cas de (*del) non existant est gere dans ft_delone
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*i;
	t_list	*p;

	if (!lst || !*lst)
		return ;
	i = *lst;
	while (i)
	{
		p = i->next;
		ft_lstdelone(i, del);
		i = p;
	}
	*lst = NULL;
}
