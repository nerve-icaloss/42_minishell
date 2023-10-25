/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:03:22 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 12:03:27 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/signal.h"

void	sigint_handler_rpel(int sigint)
{
	(void) sigint;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(int sigint)
{
	(void) sigint;
	g_signal = SIGQUIT;
}

void	sigint_handler_heredoc(int sigint)
{
	(void) sigint;
	g_signal = SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}

void	sigint_handler_failed_hd(int sigint)
{
	(void) sigint;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}

void	sigint_assign(int sigint, void (*f)(int))
{
	struct sigaction	act;

	act.sa_handler = f;
	act.sa_flags = 0;
	if (sigaction(sigint, &act, NULL) == SYS_FAIL)
		perror("sigaction");
}
