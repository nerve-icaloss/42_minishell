/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:08:57 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/29 11:21:59 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/here_doc.h"
#include "../../headers/expander.h"
#include "../../headers/signal_not_libc.h"
#include <signal.h>
#include <unistd.h>

/*
 * ret[0] is fd
 * ret[1] is expand
 * */
int	here_doc(char *eof, t_myenv *env, int expand)
{
	int		ret[2];
	char	*line;
	char	*buffer;

	if (!eof)
		return (-1);
	buffer = ft_calloc(sizeof(char), DOC_BUF);
	ret[0] = -1;
	ret[1] = expand;
	line = NULL;
	while (buffer || ret >= 0)
	{
		line = ft_readline("> ", handler_heredoc, SIG_IGN);
		if (!line && g_signal != 130)
			return (get_tmp(NULL), free(buffer), 0);
		if (!line)
			return (get_tmp(NULL), free(buffer), -1);
		if (is_eof(eof, line))
			break ;
		ret[0] = put_in_buffer(&buffer, &line, env, ret);
		free(line);
	}
	if (line)
		free(line);
	return (here_done(ret[0], buffer, env));
}

/*
 * Do not call this directly
 * It's static anyway
 * */
static int	this_doc(char **val, t_myenv *env)
{
	int		fd;
	int		stdin_fd;

	fd = -1;
	if (!val || !*val)
		return (fd);
	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == SYS_FAIL)
		return (perror("dup hd"), -1);
	fd = here_doc(*val, env, expand_this_doc(*val));
	sigint_assign(SIGINT, handler_failed_hd);
	if (fd != -1)
		sigint_assign(SIGINT, handler_rpel);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	free(*val);
	*val = NULL;
	if (fd == 0 || fd == -2 || fd == -1)
		return (-1);
	return (fd);
}

static int	run_cmd_doc(t_node *cmd, t_myenv *env)
{
	t_node	*prev_doc;
	t_node	*child;
	t_node	*i;

	prev_doc = NULL;
	child = cmd->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (child->rtype == HEREDOC)
		{
			if (prev_doc)
			{
				if (close(prev_doc->fd[IN]) == SYS_FAIL)
					perror("close_doc");
				node_sibling_pop(prev_doc);
			}
			child->fd[IN] = this_doc(&child->val, env);
			if (child->fd[IN] == SYS_FAIL)
				return (1);
			prev_doc = child;
		}
		child = i;
	}
	return (0);
}

/*
 * use THIS
 * */
int	run_tree_doc(t_node *root, t_myenv *env)
{
	t_node	*child;
	t_node	*i;

	if (!root || !env)
		return (errno = ENODATA, 1);
	if (root->type == NODE_CMD)
		return (run_cmd_doc(root, env));
	child = root->first_child;
	while (child)
	{
		i = child->next_sibling;
		if (run_cmd_doc(child, env))
			return (1);
		child = i;
	}
	return (0);
}

void	close_tree_doc(t_node *root)
{
	t_node	*child;
	t_node	*i;

	if (!root)
		return (errno = ENODATA, (void) NULL);
	child = root->first_child;
	while (child)
	{
		i = child->next_sibling;
		child = i;
	}
	if (root->rtype == HEREDOC)
		if (close(root->fd[IN]) == SYS_FAIL)
			perror("close_doc");
}
