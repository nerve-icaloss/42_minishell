/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:08:57 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/15 16:54:06 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "find_utils.h"
#include "expansion_var.h"

/*
 * Do not call this directly
 * It's static anyway
 * */
static int	this_doc(char **val, int *fd, t_myenv *myenv)
{
	char	*a;
	long	i;

	*fd = -1;
	a = *val;
	i = -1;
	if (*a == '\'' || *a == '"')
	{
		i = find_closing_quote(a);
		a[i] = '\0';
		myenv = NULL;
	}
	*fd = here_doc(a + (i >= 0), myenv);
	free(*val);
	*val = NULL;
	if (*fd < 0)
		return (-1);
	return (0);
}

/*
 * use THIS
 * */
int	run_doc(t_node *root, t_myenv *myenv)
{
	t_node	*child;
	t_node	*i;

	if(!root)
		return (errno = ENODATA, -1);
	child = root->first_child;
	while(child)
	{
		i = child->next_sibling;
		if (run_doc(child, myenv))
			return (-1);
		child = i;
	}
	if (root->redir == HEREDOC)
		if (this_doc(&root->val, &root->fd, myenv))
			return (-1);
	return (0);
}

/*
 * Use myenv == NULL to disable var_expansion
 * multiply by 1 or 0 if needed
 * line[1] is the line just readed and line[0] is all concatened lines.
 * */
int	here_doc(char *eof, t_myenv *myenv)
{
	int		len[2];
	int		fd[2];
	char	*line;

	(void) myenv;
	if (!eof || pipe(fd))
		return (-1);
	len[0] = ft_strlen(eof);
	line = readline("> ");
	len[1] = ft_strlen(line);
	while (line && (len[1] != len[0] || ft_strncmp(line, eof, len[0]) != 0))
	{
		if (myenv)
			var_expansion(&line, myenv);
		if (!line)
			break ;
		write(fd[1], line, len[1]);
		write(fd[1], "\n", 1);
		line = readline("> ");
		len[1] = ft_strlen(line);
	}
	close(fd[1]);
	if (!line)
		return (close(fd[0]), -1);
	return (fd[0]);
}
