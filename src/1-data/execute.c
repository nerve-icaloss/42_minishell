/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:04:55 by nserve            #+#    #+#             */
/*   Updated: 2023/10/25 12:42:55 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	realloc_argv(t_execute *exec)
{
	char	**new_buf;
	int		new_len;

	new_len = exec->argv_size * 2;
	new_buf = malloc(sizeof(char *) * new_len);
	if (!new_buf)
		return (errno = ENOMEM, 1);
	ft_memset(new_buf, 0, sizeof(char *) * new_len);
	while (--exec->argv_size >= 0)
		new_buf[exec->argv_size] = exec->argv[exec->argv_size]; //argv_size may be undefined
	free(exec->argv);
	exec->argv = new_buf;
	exec->argv_size = new_len;
	return (0);
}

/*
* returns 1 if the buffer is alloc'd/extended, 0 otherwise.
*/
int	check_argv_bounds(t_execute *exec)
{
	if (exec->argc >= exec->argv_size - 1)
	{
		if (!exec->argv)
		{
			exec->argv = malloc(sizeof(char *) * 32);
			if (!exec->argv)
				return (errno = ENOMEM, 0);
			ft_memset(exec->argv, 0, sizeof(char *) * 32);
			exec->argv_size = 32;
		}
		else
			if (realloc_argv(exec))
				return (0);
	}
	return (1);
}

int	add_to_argv(t_execute *exec, t_node *word)
{
	while (word)
	{
		if (check_argv_bounds(exec))
		{
			exec->argv[exec->argc] = ft_strdup(word->val);
			if (!exec->argv[exec->argc])
				return (1);
			exec->argc++;
		}
		word = word->next_sibling;
	}
	return (0);
}

void	exec_reset(t_execute *exec)
{
	int	i;

	i = 0;
	while (i < exec->argc)
	{
		free(exec->argv[i]);
		i++;
	}
	ft_memset(exec->argv, 0, sizeof (char *) * exec->argv_size);
	exec->argc = 0;
	exec->builtin_f = NULL;
	exec->bracket_first_child = NULL;
}

void	exec_clean(t_execute *exec)
{
	if (exec->argv)
		ft_arrclear(exec->argv);
}
/*
char	**build_argv(t_node *cmd)
{
	char	**argv;
	t_node	*child;
	t_node	*i;
	int		j;

	if (!cmd)
		return (errno = ENODATA, NULL);
	argv = malloc(sizeof(char *) * (cmd->children + 1));
	if (!argv)
		return (errno = ENOMEM, NULL);
	ft_memset(argv, 0, sizeof(char *) * (cmd->children + 1));
	child = cmd->first_child;
	j = 0;
	while (child)
	{
		i = child->next_sibling;
		argv[j] = ft_strdup(child->val);
		if (!argv[j])
			return (ft_arrclear(argv), NULL);
		node_sibling_pop(child);
		j++;
		child = i;
	}
	return (argv);
}*/
