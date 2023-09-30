/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:50:30 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 15:50:32 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_run.h"
#include "cmd_heredoc.h"
#include "cmd_redir.h"
#include "cmd_path.h"
#include "cmd_error.h"
#include "cmd_builtin.h"

int	single_cmd(t_mycmd *cmd, t_myshell *shell)
{
	if (heredoc_loop(&cmd->in, shell))
		return (1);
	if (is_builtin(cmd->name))
		return (single_builtin(cmd, shell));
	cmd->pid = fork();
	if (cmd->pid == SYS_FAIL)
		perror("fork");
	if (cmd->pid == 0)
		single_child(cmd, shell);
	return (single_parent(cmd, shell));
}

int	single_builtin(t_mycmd *cmd, t_myshell *shell)
{
	if (input_redirection(cmd) == SYS_FAIL)
		return (1);
	if (output_redirection(cmd) == SYS_FAIL)
		return (1);
	return (run_builtin(cmd, shell));
}

void	single_child(t_mycmd *cmd, t_myshell *shell)
{
	if (input_redirection(cmd) == SYS_FAIL)
		return (clean_shell(shell), exit(1));
	if (output_redirection(cmd) == SYS_FAIL)
		return (clean_shell(shell), exit(1));
	run_cmd(cmd, shell);
}

int	single_parent(t_mycmd *cmd, t_myshell *shell)
{
	int	status;
	int	exit_status;

	if (cmd->pid != -1)
		waitpid(cmd->pid, &status, 0);
	unlink_loop(&cmd->in);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		return (exit_status);
	}
	return (0);
}

void	run_cmd(t_mycmd *cmd, t_myshell *shell)
{
	cmd->path = get_cmd_path(cmd->name, shell);
	if (cmd->path == NULL && errno == EISDIR)
		return (perror(cmd->name), clean_shell(shell), exit(126));
	if (cmd->path == NULL)
		return (cmd_notfound(cmd->name), clean_shell(shell), exit(127));
	if (execve(cmd->path, cmd->args, shell->env.envp) == SYS_FAIL)
	{
		perror(cmd->name);
		if (errno == ENOENT)
			return (clean_shell(shell), exit(127));
		return (clean_shell(shell), exit(1));
	}
}
