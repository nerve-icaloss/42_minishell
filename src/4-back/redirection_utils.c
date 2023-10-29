/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:50:57 by nserve            #+#    #+#             */
/*   Updated: 2023/10/29 10:59:16 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/expander.h"

static char	*check_expanded_redir(t_node *redir, t_myenv *env)
{
	char	*name;
	int		x;
	int		is_ambigous;

	name = redir_expand(redir->val, redir->rtype, env);
	if (!name)
		return (NULL);
	x = 0;
	is_ambigous = 0;
	while (name[x])
	{
		if (ft_isquote(name[x]))
			break ;
		if (ft_isspace(name[x]))
			is_ambigous++;
		x++;
	}
	if (is_ambigous)
	{
		write(2, "minishell: ", 11);
		ft_dprintf(2, "%s: ambiguous redirect\n", redir->val);
		return (free(name), NULL);
	}
	remove_quotes_str(&name);
	return (name);
}

int	open_redirection(t_node *redir, t_myenv *env)
{
	char	*name;
	int		fd;

	if (!redir)
		return (errno = ENODATA, 1);
	name = check_expanded_redir(redir, env);
	if (!name)
		return (-1);
	fd = -1;
	if (name && redir->rtype == READ)
		fd = open_read(name);
	if (redir->rtype == HEREDOC)
		fd = redir->fd[IN];
	if (name && redir->rtype == TRUNC)
		fd = open_trunc(name);
	if (name && redir->rtype == APPEND)
		fd = open_append(name);
	if (fd == SYS_FAIL)
	{
		write(2, "minishell: ", 11);
		perror(name);
	}
	return (free(name), fd);
}
