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

void	rpel_loop(t_myshell *shell)
{
	char	*cmdline;

	while (1)
	{
		cmdline = readline("minishell-1.0$ ");
		if (!cmdline || cmdline[0] == '\0' || ft_strncmp(cmdline, "\n", 1) == 0)
		{
			free(cmdline);
			continue ;
		}
		if (entry_add(&shell->history, cmdline) == -1)
			write(2, "error login history", 19);
		printf("--> %s\n", cmdline);
		//build_dexectree();
		//shell.exit = run_exectree();
		//clear_exectree();
		free(cmdline);
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
	load_history();
	shell = shell_init();
	if (argc)
	{
		rpel_loop(&shell);
	}
	exit = shell.exit;
	return(register_history(&shell.history), shell_clean(&shell), exit);
}
