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

int	cmdtab_init(t_cmdtab *tab, int cmd_count)
{
	int			i;

	if (!tab || cmd_count < 1)
		return (-1);
	tab = malloc(sizeof(*tab) * (cmd_count + 1));
	if (!tab)
		return (-1);
	i = 0;
	while (i < cmd_count)
	{
		tab[i] = cmd_init();
		if (!tab[i])
			return(cmdtab_clean(tab), -1);
		i++;
	}
	tab[i] = NULL;
	return (0);
}

void	cmdtab_clean(t_cmdtab *tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i]->path)
			free(tab[i]->path);
		if (tab[i]->name)
			free(tab[i]->name);
		if (tab[i]->args)
			ft_arrclear(tab[i]->args);
		if (tab[i]->in)
			redirtab_clean(&tab[i]->in);
		if (tab[i]->out)
			redirtab_clean(&tab[i]->out);
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
