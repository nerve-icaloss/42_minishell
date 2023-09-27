/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:57:45 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/10 14:58:30 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "history.h"

void	init_shell(t_myshell *shell)
{
	shell->history = NULL;
	shell->readline = NULL;
	shell->exectree = NULL;
}

void	prompt_loop(t_myshell *shell)
{
	int	n;
	//fct signal to put here
	if (!shell->readline)
		load_history();
	n = 0;
	while (n < 5)
	{
		shell->readline = readline("minishell-1.0$ ");
		ft_add_history(&shell->history, new_entry(shell->readline));
		printf("--> %s\n", shell->readline);
		free(shell->readline);
		n++;
	}
}

int	main(int argc, char *argv[])
{
	t_myshell	shell;
	char	*args[2];

	args[0] = "ls";
	args[1] = "-l";
	printf("Welcom to %s\n", argv[0]);
	init_shell(&shell);
	if (argc)
	{
		prompt_loop(&shell);
	}
	return(register_history(&shell.history), 0);
}
