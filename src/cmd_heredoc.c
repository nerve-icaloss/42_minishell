/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:49:57 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 14:50:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_heredoc.h"
#include "cmd_error.h"
#include "open_utils.h"

int	heredoc_cmdtab(t_cmdtab *cmdtab, t_myshell *shell)
{
	int		i;
	char	*cmd_id;

	i = 0;
	while (cmdtab[i])
	{
		if (heredoc_loop(&cmdtab[i]->in, shell) == SYS_FAIL)
			return (SYS_FAIL);
		i++;
	}
	return (0);
}

int	heredoc_loop(t_redirtab *redirtab, t_myshell *shell)
{
	int		i;
	char	*prefix;
	char	*name;

	i = 0;
	while (redirtab[i])
	{
		if (redirtab[i]->redir == o_doc)
			if (read_stdin(redirtab[i], shell) == SYS_FAIL)
				return (SYS_FAIL);
		i++;
	}
	return (0);
}

int	read_stdin(t_myredir *redir, t_myshell *shell)
{
	int		fd;
	int		len;
	char	*buffer;

	fd = open_trunc(redir->file);
	if (fd == SYS_FAIL)
		return (perror(redir->file), SYS_FAIL);
	len = ft_strlen(redir->limiter);
	buffer = readline(">");
	while (ft_strncmp(buffer, redir->limiter, len) != 0)
	{
		if (redir->expand == true)
			buffer = expand_param_str(buffer, shell);
		ft_putstr_fd(buffer, fd);
		free(buffer);
		buffer = readline(">");
	}
	free(buffer);
	if (close(fd) == SYS_FAIL)
		perror(redir->file);
	return (0);
}

void	unlink_cmdtab(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (cmdtab[i])
	{
		unlink_loop(&cmdtab[i]->in);
		i++;
	}
}

void	unlink_loop(t_redirtab *redirtab)
{
	int	i;

	i = 0;
	while (redirtab[i])
	{
		if (redirtab[i]->redir == o_doc)
			if (unlink(redirtab[i]->file) == SYS_FAIL)
				perror(redirtab[i]->file);
		i++;
	}
}
