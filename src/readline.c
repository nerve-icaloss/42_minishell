/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:49 by marvin            #+#    #+#             */
/*   Updated: 2023/09/14 17:42:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "readline.h"
#include "history.h"
#include <stdlib.h>

void	prompt_loop(t_myshell *shell)
{
	//fct signal to put here
	if (!shell->input.content)
		load_history(shell);
	while (1)
	{
		shell->input.content = readline("minishell-1.0$ ");
		ft_add_history(shell->input.content);
		printf("--> %s\n", shell->input.content);
		free(shell->input.content);
	}

}
