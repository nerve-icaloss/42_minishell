/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:56:40 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 17:56:42 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../headers/minishell.h"

void	reset_redirection(t_execute *exec);
int apply_redirection(t_execute *exec);
int infile_redirection(t_execute *exec, t_node *cmd);
int outfile_redirection(t_execute *exec, t_node *cmd);
void close_prev_redirection(t_execute *exec, int fd);

#endif
