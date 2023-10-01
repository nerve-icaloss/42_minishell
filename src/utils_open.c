/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:59 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 11:21:29 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_utils.h"

int	open_read(char *file)
{
	return (open(file, O_RDONLY));
}

int	open_append(char *file)
{
	return (open(file, O_CREAT | O_WRONLY | O_APPEND, 000666));
}

int	open_trunc(char *file)
{
	return (open(file, O_CREAT | OWRONLY | O_TRUNC, 000666));
}
