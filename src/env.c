/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 13:53:07 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	while (*envp)
	{
		if (var_parsing(&myenv->lst_var, *envp))
			return (var_clean(&myenv->lst_var), -1);
		envp++;
	}
	myenv->pwd = var_get(myenv->lst_var, "PWD");
	myenv->oldpwd = var_get(myenv->lst_var, "OLDPWD");
	myenv->home = var_get(myenv->lst_var, "HOME");
	return (0);
}
