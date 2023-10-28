/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:35:07 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 12:10:15 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pwd_builtin(char **argv, t_myenv *env)
{
	char	*pwd;

	(void) argv;
	pwd = ft_getcwd(env);
	if (!pwd)
		return (ft_dprintf(2, "pwd: %s\n", strerror(errno)), 1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
