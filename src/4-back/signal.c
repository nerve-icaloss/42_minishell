/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:03:22 by nserve            #+#    #+#             */
/*   Updated: 2023/10/29 18:13:30 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/signal_not_libc.h"

void	handler_rpel(int signum)
{
	(void) signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_child(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handler_heredoc(int signum)
{
	(void) signum;
	close(STDIN_FILENO);
	g_signal = 130;
	write(1, "\n", 1);
}

void	handler_failed_hd(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_assign(int signum, void (*f)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = f;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) == SYS_FAIL)
		perror("sigaction");
}
