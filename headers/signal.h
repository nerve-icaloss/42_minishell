/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:03:32 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:23:24 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

extern volatile int	g_signal;

void	sigint_handler_rpel(int sigint);
void	sigint_handler_child(int sigint);
void	sigint_handler_heredoc(int sigint);
void	sigint_handler_failed_hd(int sigint);

void	sigint_assign(int sigint, void (*f)(int));


#endif
