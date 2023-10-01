/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_redirtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:27:59 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 10:28:09 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_myredir *redir_init()
{
	t_myredir *redir;

	redir = malloc(sizeof(*redir));
	if (!redir)
		return (NULL);
	redir->redir = 0;
	redir->limiter = NULL;
	redir->expand = true;
	redir->fd = -1;
	redir->file = NULL;
	return (redir);
}

int	redirtab_init(t_redirtab *tab, int redir_count)
{
	int			i;

	if (!tab || redir_count < 1)
		return (-1);
	tab = malloc(sizeof(*tab) * (redir_count + 1));
	if (!tab)
		return (-1);
	i = 0;
	while (i < redir_count)
	{
		tab[i] = redir_init();
		if (!tab[i])
			return (redirtab_clean(tab), -1);
		i++;
	}
	tab[i] = NULL;
	return (0);

}

void	redirtab_clean(t_redirtab *tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i]->limiter)
			free(tab[i]->limiter);
		if (tab[i]->file)
			free(tab[i]->file);
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
