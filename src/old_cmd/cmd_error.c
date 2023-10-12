/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:22:11 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 14:22:13 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_error.h"
#include "libft/libft.h"
#include <string.h>

void	cmd_notfound(char *str)
{
	char	*strerror;
	char	*not_found;

	not_found = ": command not found";
	strerror = ft_strjoin(str, not_found);
	write(2, strerror, ft_strlen(strerror));
	free(strerror);
}

void	path_notfound(void)
{
	write(2, "env: path not found", 19);
}
