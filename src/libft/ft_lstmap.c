/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:04:10 by hmelica           #+#    #+#             */
/*   Updated: 2023/04/08 12:56:12 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
Condition d'existence de del dans lstclear
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*to_return;

	to_return = NULL;
	while (lst)
	{
		if (f)
			elem = ft_lstnew((*f)(lst->content));
		else
			elem = ft_lstnew(lst->content);
		if (!elem || !elem->content)
		{
			ft_lstclear(&to_return, del);
			return (NULL);
		}
		ft_lstadd_back(&to_return, elem);
		lst = lst->next;
	}
	return (to_return);
}
