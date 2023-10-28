/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:56:40 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:22:54 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "minishell.h"

int		apply_redirection(t_execute *exec, t_node *cmd);
int		reset_redirection(t_execute *exec, t_node *cmd);

int		open_redirection(t_node *redir, t_myenv *env);
int		infile_redirection(t_node *cmd, t_node *redir, t_myenv *env);
int		outfile_redirection(t_node *cmd, t_node *redir, t_myenv *env);
int		do_redirection(t_node *cmd, t_myenv *env);

#endif
