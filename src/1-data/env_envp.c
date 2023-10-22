/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:34:40 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 16:57:04 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
 * if env has been modified by something else than export and unset, 
 * run env_update_count before this
 * t_done */
int	envp_update(t_myenv *env)
{
	t_lstvar	lst;
	char		**envp;

	if (!env)
		return (-1);
	envp_clean(&env->envp);
	lst = env->lst_var;
	env->envp = malloc(sizeof(char *) * (env->count + 1));
	ft_bzero(env->envp, sizeof(char *) * (env->count + 1));
	if (!env->envp)
		return (-1);
	envp = env->envp;
	while (lst)
	{
		if (!lst->value || *lst->value == '\0')
		{
			lst = lst->next;
			continue ;
		}
		*envp = var_get_string(lst);
		if (!*(envp++))
			return (envp_clean(&env->envp), -1);
		lst = lst->next;
	}
	return (0);
}
