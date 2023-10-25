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

#ifndef SIGNAL_NOT_LIBC_H
# define SIGNAL_NOT_LIBC_H

# include "minishell.h"

void	handler_rpel(int signum);
void	handler_child(int signum);
void	handler_heredoc(int signum);
void	handler_failed_hd(int signum);

void	sigint_assign(int signum, void (*f)(int));


#endif
