/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:04:55 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 16:57:27 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
}

void	exec_clean(t_execute *exec)
{
	if (exec->argv)
		ft_arrclear(exec->argv);
	exec->argv = NULL;
}
