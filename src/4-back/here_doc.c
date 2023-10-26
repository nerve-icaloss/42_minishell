/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:08:57 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/26 15:41:14 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/here_doc.h"
#include "../../headers/expander.h"

/*
 * Use myenv == NULL to disable var_expansion
 * multiply by 1 or 0 if needed
 * line[1] is the line just readed and line[0] is all concatened lines.
 * */
int	here_doc(char *eof, t_myenv *env)
{
	int		len[2];
	int		fd[2];
	char	*line;

	(void) env;
	if (!eof || pipe(fd))
		return (-1);
	len[0] = ft_strlen(eof);
	line = readline("> ");
	len[1] = ft_strlen(line);
	while (line && (len[1] != len[0] || ft_strncmp(line, eof, len[0]) != 0))
	{
		if (env)
			var_expansion(&line, env);
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		line = readline("> ");
		len[1] = ft_strlen(line);
	}
	close(fd[1]);
	if (!line)
		return (close(fd[0]), -1);
	return (fd[0]);
}

/*
 * Do not call this directly
 * It's static anyway
 * */
static int	this_doc(char **val, t_myenv *env)
{
	char	*a;
	long	i;
	int		fd;

	fd = -1;
	a = *val;
	i = -1;
	if (*a == '\'' || *a == '"')
	{
		i = find_closing_quote(a);
		a[i] = '\0';
		env = NULL;
	}
	fd = here_doc(a + (i >= 0), env);
	free(*val);
	*val = NULL;
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
