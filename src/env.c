/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 11:29:35 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_clean(t_myenv *myenv)
{
	var_clean(&myenv->lst_var);
	envp_clean(&myenv->envp);
	myenv->count = 0;
	myenv->pwd = NULL;
	myenv->oldpwd = NULL;
	myenv->home = NULL;
}

int	env_update_count(t_myenv *myenv)
{
	t_lstvar	lst;

	if (!myenv)
		return (-1);
	lst = myenv->lst_var;
	myenv->count = 0;
	while (lst)
	{
		if (lst->value)
			myenv->count++;
		lst = lst->next;
	}
	return (0);
}

/*
 * Description :
 * Init myenv using envp
 *   - myenv is unitialized at the begining
 *   - doesnt check if pwd, oldpwd or home are set at the end
 * */
int	env_init(t_myenv *myenv, char **envp)
{
	if (!envp || !myenv)
		return (-1);
	myenv->lst_var = NULL;
	myenv->envp = NULL;
	while (*envp)
	{
		if (var_parsing(&myenv->lst_var, *envp))
			return (var_clean(&myenv->lst_var), -1);
		envp++;
	}
	myenv->pwd = var_get(myenv->lst_var, "PWD");
	myenv->oldpwd = var_get(myenv->lst_var, "OLDPWD");
	myenv->home = var_get(myenv->lst_var, "HOME");
	if (env_update_count(myenv) || envp_update(myenv))
		return (var_clean(&myenv->lst_var), -1);
	return (0);
}

/*
 * there is no params needed
 * */
int	env_builtin(t_myenv *myenv)
{
	t_lstvar	var;

	var = myenv->lst_var;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
	return (0);
}
