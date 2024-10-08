/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:59 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:18:23 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_read(char *file)
{
	return (open(file, O_RDONLY));
}

int	open_append(char *file)
{
	return (open(file, O_CREAT | O_WRONLY | O_APPEND, 0666));
}

int	open_trunc(char *file)
{
	return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666));
}
