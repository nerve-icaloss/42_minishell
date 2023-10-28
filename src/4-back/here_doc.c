/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:08:57 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 15:40:36 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/here_doc.h"
#include "../../headers/expander.h"
#include "../../headers/signal_not_libc.h"
#include <signal.h>
#include <unistd.h>

/*
 * Use myenv == NULL to disable var_expansion
 * multiply by 1 or 0 if needed
 * line[1] is the line just readed and line[0] is all concatened lines.
 * */
int	here_doc(char *eof, t_myenv *env)
{
	int		fd[2];
	int		ret;
	char	*line;

	if (!eof || pipe(fd))
		return (-1);
	while (1)
	{
		line = ft_readline("> ", handler_heredoc, SIG_IGN);
		if (!line && g_signal != 130)
			return (close(fd[1]), close(fd[0]), 0);
		if (!line)
			return (close(fd[1]), close(fd[0]), g_signal = -1, -1);
		ret = doc_happend(line, eof, fd[1], env);
		if (ret != 2)
		{
			if (ret == 0)
				return (close(fd[1]), fd[0]);
			else
				return (close(fd[1]), close(fd[0]), ret);
		}
	}
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
	env = expand_this_doc(val, env);
	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == SYS_FAIL)
		return (perror("dup hd"), -1);
	fd = here_doc(*val, env);
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
