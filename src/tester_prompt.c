/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:32:39 by marvin            #+#    #+#             */
/*   Updated: 2023/09/14 18:43:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

	init_shell(&shell);
	if (argc)
	{
	}
	return(EXIT_SUCCESS);
}
