/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:27:00 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 10:29:41 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_pipex.h"
#include "cmd_heredoc.h"
#include "cmd_redir.h"
#include "cmd_run.h"
#include "cmd_pipe.h"
#include "cmd_builtin.h"

int	pipex_cmd(t_cmdtab *cmdtab, int cmd_count, t_myshell *shell)
{
	int		*pipe_fd;
	int		i;

	i = 0;
	if (heredoc_cmdtab(cmdtab, shell) && init_pipe(&pipe_fd))
		return (pipex_parent(cmdtab, shell));
	while (i < cmd_count)
	{
		if (open_pipe(cmdtab, &pipe_fd, cmd_count, i) == SYS_FAIL)
			return (perror("pipe"), free(pipe_fd), pipex_parent(cmdtab, shell));
		cmdtab[i]->pid = fork();
		if (cmdtab[i]->pid == SYS_FAIL)
			return (perror("fork"), free(pipe_fd), pipex_parent(cmdtab, shell));
		if (cmdtab[i]->pid == 0)
			pipex_child(cmdtab, &pipe_fd, i, shell);
		if (close_parent_pipe(cmdtab, pipe_fd, i, cmd_count) == SYS_FAIL)
			return (free(pipe_fd), pipex_parent(cmdtab, shell));
		i++;
	}
	return (free(pipe_fd), pipex_parent(cmdtab, shell));
}

void	pipex_child(t_cmdtab *cmdtab, int **pipe_fd, int id, t_myshell *shell)
{
	int	cmd_count;

	cmd_count = 0;
	while (cmdtab[cmd_count])
		cmd_count++;
	if (close_child_pipe(*pipe_fd, id, cmd_count) == SYS_FAIL)
		return (free(*pipe_fd), shell_clean(shell), exit(1));
	if (input_redirection(cmdtab[id]) == SYS_FAIL)
		return (free(*pipe_fd), shell_clean(shell), exit(1));
	free(*pipe_fd);
	if (output_redirection(cmdtab[id]) == SYS_FAIL)
		return (shell_clean(shell), exit(1));
	if (cmdtab[id]->args[0][0] == '\0')
		return (shell_clean(shell), exit(0));
	if (is_builtin(cmdtab[id]->name))
		exit(run_builtin(cmdtab[id], shell));
	else
		run_cmd(cmdtab[id], shell);
}

int	pipex_parent(t_cmdtab *cmdtab, t_myshell *shell)
{
	int	status;
	int	exit_status;
	int	i;

	i = 0;
	while (cmdtab[i])
	{
		if (cmdtab[i]->pid != -1)
			waitpid(cmdtab[i]->pid, &status, 0);
		unlink_loop(&cmdtab[i]->in);
		i++;
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		return (exit_status);
	}
	return (0);
}
