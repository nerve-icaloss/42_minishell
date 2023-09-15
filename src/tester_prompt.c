/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:32:39 by marvin            #+#    #+#             */
/*   Updated: 2023/09/15 14:36:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline.h"
#include "history.h"

void	init_shell(t_myshell *shell)
{
	shell->history = NULL;
	shell->env = NULL;
	shell->input.content = NULL;
	shell->parsing = NULL;
	shell->exec = NULL;
}

int	main(int argc, char *argv[])
{
	t_myshell	shell;
	t_myhistory	log;

	printf("Welcom to %s\n", argv[0]);
	init_shell(&shell);
	if (argc)
	{
		prompt_loop(&shell);
	}
	log = *shell.history;
	while (log)
	{
		printf("log: %s\n", log->content);
		log = log->next;
	}
	return(register_history(shell.history), EXIT_SUCCESS);
}
