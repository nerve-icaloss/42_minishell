/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/29 10:27:34 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
 * T */
void	env_clean(t_myenv *myenv)
{
	var_clean(&myenv->lst_var);
	envp_clean(&myenv->envp);
	myenv->count = 0;
	myenv->pwd = NULL;
	myenv->oldpwd = NULL;
	myenv->home = NULL;
}

/*
 * T */
int	env_update_count(t_myenv *myenv)
{
	t_lstvar	lst;

	if (!myenv)
		return (-1);
	lst = myenv->lst_var;
	myenv->count = 0;
	while (lst)
	{
		if (lst->value && *lst->value != '\0')
			myenv->count++;
		lst = lst->next;
	}
	return (0);
}

/*
 * init PWD, OLDPWD and SHLVL
 * Do increment SHLVL
 * */
int	env_default(t_myenv *myenv)
{
	t_lstvar	shlvl;
	int			i;

	shlvl = var_get(myenv->lst_var, "PWD");
	if (shlvl)
		free(shlvl->value);
	else
	{
		if (var_add(&myenv->lst_var, ft_strdup("PWD"), NULL))
			return (-1);
		shlvl = myenv->lst_var;
	}
	shlvl->value = getcwd(NULL, 0);
	if (!var_get(myenv->lst_var, "OLDPWD"))
		if (var_add(&myenv->lst_var, ft_strdup("OLDPWD"), NULL))
			return (-1);
	shlvl = var_get(myenv->lst_var, "SHLVL");
	if (!shlvl)
		return (var_add(&myenv->lst_var, ft_strdup("SHLVL"), ft_strdup("1")));
	i = ft_atoi(shlvl->value) + 1;
	if (i < 1)
		i = 1;
	free(shlvl->value);
	shlvl->value = ft_itoa(i);
	return (0);
}

/*
 * Description :
 * Init myenv using envp
 *   - myenv is unitialized at the begining
 *   - doesnt check if pwd, oldpwd or home are set at the end
 * T */
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
	env_default(myenv);
	myenv->pwd = var_get(myenv->lst_var, "PWD");
	myenv->oldpwd = var_get(myenv->lst_var, "OLDPWD");
	myenv->home = var_get(myenv->lst_var, "HOME");
	if (env_update_count(myenv) || envp_update(myenv))
		return (var_clean(&myenv->lst_var), -1);
	return (0);
}

/*
 * there is no params needed
 * T */
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
