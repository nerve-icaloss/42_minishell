/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:44:29 by marvin            #+#    #+#             */
/*   Updated: 2023/09/14 18:43:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "history.h"
#include <stdlib.h>
#include <readline/history.h>

void	ft_add_history(t_myshell *shell)
{
	t_myhistory	*new;
	t_myhistory	*current;

	new = malloc(sizeof(*new));
	if (!new)
		return ;
	new->content = shell->input.content;
	new->next = NULL;
	if (!shell->history)
		shell->history = new;
	else
	{
		current = shell->history;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	add_history(shell->input.content);
}

void	ft_clear_history(t_myshell *shell)
{
	t_myhistory	*current;
	t_myhistory	*todel;

	if (!shell->history)
		return ;
	current = shell->history;
	while (current)
	{
		todel = current;
		current = current->next;
		free(todel);
	}
	shell->history = NULL;
}

void	load_history(t_myshell *shell)
{


}

void	save_history(t_myshell *shell)
{

	ft_clear_history(shell);
}
