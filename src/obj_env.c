/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:41:30 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 14:41:32 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "var_utils.h"

/*
 * init PWD, OLDPWD and SHLVL
 * Do increment SHLVL
 * */
int	env_default(t_myenv *env)
{
	t_lstvar	shlvl;
	int			i;

	shlvl = var_get(env->lst_var, "PWD");
	if (shlvl)
		free(shlvl->value);
	else
	{
		if (var_add(&env->lst_var, ft_strdup("PWD"), NULL))
			return (-1);
		shlvl = env->lst_var;
	}
	shlvl->value = getcwd(NULL, 0);
	if (!var_get(env->lst_var, "OLDPWD"))
		if (var_add(&env->lst_var, ft_strdup("OLDPWD"), NULL))
			return (-1);
	shlvl = var_get(env->lst_var, "SHLVL");
	if (!shlvl)
		return (var_add(&env->lst_var, ft_strdup("SHLVL"), ft_strdup("1")));
	i = ft_atoi(shlvl->value) + 1;
	if (i < 1)
		i = 1;
	free(shlvl->value);
	shlvl->value = ft_itoa(i);
	return (0);
}

/*
 * T */
int	env_update_count(t_myenv *env)
{
	t_lstvar	lst;

	if (!env)
		return (-1);
	lst = env->lst_var;
	env->count = 0;
	while (lst)
	{
		if (lst->value && *lst->value != '\0')
			env->count++;
		lst = lst->next;
	}
	return (0);
}

/*
 * Description :
 * Init myenv using envp
 *   - myenv is unitialized at the begining
 *   - doesnt check if pwd, oldpwd or home are set at the end
 * T */
int	env_init(t_myenv *env, char **envp)
{
	if (!envp || !env)
		return (-1);
	env->lst_var = NULL;
	env->envp = NULL;
	while (*envp)
	{
		if (var_parsing(&env->lst_var, *envp))
			return (var_clean(&env->lst_var), -1);
		envp++;
	}
	env_default(env);
	env->pwd = var_get(env->lst_var, "PWD");
	env->oldpwd = var_get(env->lst_var, "OLDPWD");
	env->home = var_get(env->lst_var, "HOME");
	if (env_update_count(env) || envp_update(env))
		return (var_clean(&env->lst_var), -1);
	return (0);
}

/*
 * T */
void	env_clean(t_myenv *env)
{
	var_clean(&env->lst_var);
	envp_clean(&env->envp);
	env->count = 0;
	env->pwd = NULL;
	env->oldpwd = NULL;
	env->home = NULL;
}
