/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:31 by nserve            #+#    #+#             */
/*   Updated: 2023/10/17 11:42:37 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executor.h"
#include "../../headers/here_doc.h"

void	child_cmd(t_execute *exec, t_myshell *shell)
{
	close_tree_doc(shell->root);
	if (exec->std_fd[IN] > -1)
		close(exec->std_fd[IN]);
	if (exec->std_fd[OUT] > -1)
		close(exec->std_fd[OUT]);
	if (execve(exec->argv[0], exec->argv, shell->env.envp) == SYS_FAIL)
	{
		perror(exec->argv[0]);
		exit(1);
	}
}

void	child_pipex_cmd(t_execute *exec, t_myshell *shell)
{
	close_tree_doc(shell->root);
	close(exec->toclose_child);
	if (exec->std_fd[IN] > -1)
		close(exec->std_fd[IN]);
	if (exec->std_fd[OUT] > -1)
		close(exec->std_fd[OUT]);
	if (exec->bracket_first_child)
	{
		//exec->exit = execute_tree(exec->bracket_first_child, shell);
		shell_clean(shell);
		exit(exec->exit);
	}
	if (exec->builtin_f)
	{
		exec->exit = exec->builtin_f(exec->argv, &shell->env);
		ft_arrclear(exec->argv);
		exit(exec->exit);
	}
	if (execve(exec->argv[0], exec->argv, shell->env.envp) == SYS_FAIL)
	{
		perror(exec->argv[0]);
		exit(1);
	}
}
