/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:28:16 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 09:28:23 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_redir.h"
#include "expansion_utils.h"
#include "find_utils.h"

t_node	*new_redir(char *data, t_redir_type type)
{
	t_node	*redir;

	if (!data)
		return (errno = ENODATA, NULL);
	redir = node_new(NODE_WORD);
	if (!redir)
		return (errno = ENOMEM, NULL);
	if (node_val_set(redir, data) == -1)
		return (node_tree_clean(redir), NULL);
	redir->rtype = type;
	return (redir);
}

t_node	*redir_expansion(char *data, t_redir_type type, t_myenv *env)
{
	t_node		*redir;
	t_expand	expd;

	if (!data || !*data || !env)
		return (errno = ENODATA, NULL);
	if (expand_init(&expd, data))
		return (NULL);
	find_expansion(&expd, env);
	redir = new_redir(expd.pstart, type);
	if (!redir)
		return (NULL);
	free(expd.pstart);
	//if (type != HEREDOC)
	//	remove_quotes(redir);
	return (redir);
}
