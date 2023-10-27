/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:59:24 by nserve            #+#    #+#             */
/*   Updated: 2023/10/27 21:37:53 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	entry_add(t_history *origin, char *str)
{
	t_myentry	*to_add;
	t_myentry	*i;

	if (!origin || !str)
		return (-1);
	add_history(str);
	to_add = malloc(sizeof(*to_add));
	if (!to_add)
		return (-1);
	to_add->content = ft_strdup(str);
	to_add->next = NULL;
	i = *origin;
	while (i && i->next)
		i = i->next;
	if (!i)
		*origin = to_add;
	else
		i->next = to_add;
	return (0);
}

void	history_clean(t_history *origin)
{
	t_myentry	*i;

	if (!*origin)
		return ;
	i = *origin;
	while (i)
	{
		*origin = (*origin)->next;
		free(i->content);
		free(i);
		i = *origin;
	}
	*origin = NULL;
}

void	load_history(void)
{
	int		fd;
	char	*buffer;
	char	*nl;
	char	*file;

	file = ft_strjoin2(getcwd(NULL, 0), HISTORY_FILE, 1, 0);
	if (!file)
		return ;
	fd = open(file, O_RDONLY, 000666);
	free(file);
	if (fd == -1)
		return ;
	buffer = get_next_line(fd);
	while (buffer)
	{
		nl = ft_strchr(buffer, '\n');
		if (nl)
			*nl = '\0';
		add_history(buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	if (close(fd) == -1)
		return ;
}

void	register_history(t_myshell *shell)
{
	int			fd;
	t_history	i;
	char		*log;
	char		*file;

	if (!shell->hist)
		return ;
	file = ft_strjoin(shell->start_dir, HISTORY_FILE);
	fd = open_append(file);
	if (fd == -1)
		return (perror(file), free(file));
	free(file);
	i = shell->hist;
	while (i)
	{
		log = ft_strjoin(i->content, "\n");
		write(fd, log, ft_strlen(log));
		free(log);
		i = i->next;
	}
	rl_clear_history();
	history_clean(&shell->hist);
	if (close(fd) == -1)
		return ;
}
