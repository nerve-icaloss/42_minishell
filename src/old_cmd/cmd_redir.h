/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:56:10 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 12:56:18 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_REDIR_H
# define CMD_REDIR_H

# include "../headers/minishell.h"

int input_redirection(t_mycmd *cmd);
int output_redirection(t_mycmd *cmd);
int open_loop(t_redirtab *redirtab, int count);
void close_loop(t_redirtab *redirtab, int count);

#endif
