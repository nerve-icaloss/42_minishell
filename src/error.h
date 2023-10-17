/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:54:08 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 18:54:16 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ERROR_H
# define CMD_ERROR_H

# include "../headers/minishell.h"

void	cmd_notfound(char *str);
void	path_notfound(void);

#endif
