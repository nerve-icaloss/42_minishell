/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:04:42 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 12:04:47 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/signal.h"

char	*ft_readline(char *prompt, void (*signal_handler)(int), 
				  void (*signal_restore))
{
	int	std_out;
	char	*ret;

	sigint_assign(SIGINT, signal_handler);
	if (isatty(STDIN_FILENO))
	{
		std_out = dup(STDOUT_FILENO);
		if (std_out == SYS_FAIL)
			return (perror("dup"), NULL);
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == SYS_FAIL)
			return (perror("dup2"), NULL);
		ret = readline(prompt);
		if (close (STDOUT_FILENO) == SYS_FAIL)
			perror("close");
		if (dup2(std_out, STDOUT_FILENO) == SYS_FAIL)
			return (perror("dup2"), NULL);
		if (close (std_out) == SYS_FAIL)
			perror("close");
	}
	sigint_assign(SIGINT, signal_restore);
	return (ret);
}
