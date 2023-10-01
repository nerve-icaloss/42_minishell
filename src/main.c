/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:57:45 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 09:34:09 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "history.h"

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
		if (!shell->readline)
		{
			free(shell->readline);
			break ;
		}
		if (entry_add(&shell->history, shell->readline) == -1)
			write(2, "error login history", 19);
		printf("--> %s\n", shell->readline);
		//build_dexectree();
		//shell.exit = run_exectree();
		//clear_exectree();
		free(shell->readline);
		n++;
	}
}

int	main(int argc, char *argv[])
{
	t_myshell	shell;
	char		*args[2];
	int			exit;

	(void) args;
	printf("Welcom to %s\n", argv[0]);
	shell = shell_init();
	if (argc)
	{
		prompt_loop(&shell);
	}
	exit = shell.exit;
	return(register_history(&shell.history), shell_clean(&shell), exit);
}
