/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:11:45 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 16:11:59 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_access(char *cmd_path, t_execute *exec)
{
	if (access(cmd_path, F_OK | X_OK) == SYS_FAIL)
	{
		write(2, "minishell: ", 11);
		perror(cmd_path);
		if (errno == EACCES)
			exec->exit = 126;
		if (errno == ENOENT)
			exec->exit = 127;
		return (1);
	}
	else
		return (0);
}
