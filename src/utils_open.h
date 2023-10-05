/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:21:33 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 11:21:51 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

# include "../headers/minishell.h"

int open_read(char *file);
int open_append(char *file);
int open_trunc(char *file);

#endif
