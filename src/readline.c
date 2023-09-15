/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:49 by marvin            #+#    #+#             */
/*   Updated: 2023/09/15 14:32:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "history.h"

void	prompt_loop(t_myshell *shell)
{
	int	n;
	//fct signal to put here
	printf("input is %s - load history\n", shell->input.content);
	if (!shell->input.content)
		load_history();
	n = 0;
	while (n < 5)
	{
		shell->input.content = readline("minishell-1.0$ ");
		ft_add_history(shell->history, new_entry(shell->input.content));
		printf("--> %s\n", shell->input.content);
		free(shell->input.content);
		n++;
	}
}
