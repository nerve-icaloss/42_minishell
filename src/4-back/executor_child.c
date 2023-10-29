/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:31 by nserve            #+#    #+#             */
/*   Updated: 2023/10/29 14:32:51 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"
#include "../../headers/here_doc.h"
#include "../../headers/signal_not_libc.h"

static void	close_all_fd_child(t_execute *exec, t_myshell *shell)
{
	close_tree_doc(shell->root);
	if (exec->std_fd[IN] > -1)
		close(exec->std_fd[IN]);
	if (exec->std_fd[OUT] > -1)
		close(exec->std_fd[OUT]);
}

static void	close_std_fd_child(t_execute *exec)
{
	if (exec->std_fd[IN] > -1)
		close(exec->std_fd[IN]);
	if (exec->std_fd[OUT] > -1)
		close(exec->std_fd[OUT]);
}

static void	clean_child(t_execute *exec, t_myshell *shell)
{
	if (exec->argv)
		ft_arrclear(exec->argv);
	shell_clean(shell);
}

void	child_cmd(t_execute *exec, t_myshell *shell)
{
	sigint_assign(SIGINT, handler_child);
	close_all_fd_child(exec, shell);
	sigint_assign(SIGQUIT, SIG_DFL);
	if (execve(exec->argv[0], exec->argv, shell->env.envp) == SYS_FAIL)
		return (perror(exec->argv[0]), clean_child(exec, shell), exit(1));
}

void	child_pipex_cmd(t_execute *exec, t_myshell *shell)
{
	shell->env.subsh = true;
	sigint_assign(SIGINT, handler_child);
	if (exec->toclose_child != -1)
		close(exec->toclose_child);
	if (exec->argv && !exec->argv[0] && !exec->builtin_f && !exec->bracket_first_child)
	{
		close_all_fd_child(exec, shell);
		return (shell_clean(shell), exit (0));
	}
	if (exec->bracket_first_child)
	{
		close_std_fd_child(exec);
		exec->exit = execute_tree(exec->bracket_first_child, shell);
		return (shell_clean(shell), exit(exec->exit));
	}
	close_all_fd_child(exec, shell);
	if (exec->builtin_f)
	{
		exec->exit = exec->builtin_f(exec->argv, &shell->env);
		return (shell_clean(shell), exit(exec->exit));
	}
	sigint_assign(SIGQUIT, SIG_DFL);
	if (execve(exec->argv[0], exec->argv, shell->env.envp) == SYS_FAIL)
		return (perror(exec->argv[0]), shell_clean(shell), exit(1));
}
