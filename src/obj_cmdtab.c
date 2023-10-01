/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:51:21 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 15:51:22 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_mycmd	*cmd_init(void)
{
	t_mycmd *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->pid = -1;
	cmd->in_count = -1;
	cmd->in = NULL;
	cmd->in_fd = -1;
	cmd->path = NULL;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->out_fd = -1;
	cmd->out_count = -1;
	cmd->out = NULL;
	return (cmd);
}

t_cmdtab *cmdtab_init(int cmd_count)
{
	t_cmdtab	*cmdtab;
	int			i;

	if (cmd_count < 1)
		return (NULL);
	cmdtab = malloc(sizeof(*cmdtab) * (cmd_count + 1));
	if (!cmdtab)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		cmdtab[i] = cmd_init();
		i++;
	}
	cmdtab[i] = NULL;
	return (cmdtab);
}

void	cmdtab_clean(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (cmdtab[i])
	{
		free(cmdtab[i]);
		i++;
	}
	free(cmdtab);
	cmdtab = NULL;
}
