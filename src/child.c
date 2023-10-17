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

#include "child.h"
#include "builtin.h"
#include "here_doc.h"

void	child_cmd(t_execute *exec, t_myshell *shell)
{
	close_tree_doc(shell->root);
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
	if (is_builtin(exec->argv[0]))
	{
		exec->exit = builtin_cmd(exec->argv, shell->env);
		shell_clean(shell);
		ft_arrclear(exec->argv);
		exit(exec->exit);
	}
		exit(builtin_cmd(exec, shell));
	if (execve(exec->argv[0], exec->argv, shell->env.envp) == SYS_FAIL)
	{
		perror(exec->argv[0]);
		ft_arrclear(exec->argv);
		exit(1);
	}
}
