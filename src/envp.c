/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:34:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/22 16:32:27 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
 * t_done */
void	envp_clean(char ***envp)
{
	char	**i;

	if (!envp || !*envp)
		return ;
	i = *envp;
	while (*i)
		free(*(i++));
	free(*envp);
	*envp = NULL;
}

/*
 * t_done */
int	envp_update(t_myenv *myenv)
{
	t_lstvar	lst;
	char		**envp;

	if (!myenv)
		return (-1);
	envp_clean(&myenv->envp);
	lst = myenv->lst_var;
	myenv->envp = malloc(sizeof(char *) * (myenv->count + 1));
	ft_bzero(myenv->envp, sizeof(char *) * (myenv->count + 1));
	if (!myenv->envp)
		return (-1);
	envp = myenv->envp;
	while (lst)
	{
		if (!lst->value || *lst->value == '\0')
		{
			lst = lst->next;
			continue ;
		}
		*envp = var_get_string(lst);
		if (!*envp)
			return (envp_clean(&myenv->envp), -1);
		envp++;
		lst = lst->next;
	}
	return (0);
}
