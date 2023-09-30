/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:43:42 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 15:43:46 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exectree.h"
#include "obj_exectree.h"
#include "cmd_syntax.h"
#include "cmdtab.h"

int	build_exectree(t_exectree *exectree, char *readline)
{
	if (check_syntax_exec(readline))
		return (2);
	*exectree = new_exec(readline);
	if (!*exectree)
		return (1);
	else
		return (0);
}

int	run_exectree(t_myshell *shell)
{
	shell->exit = run_exec(shell->exectree, shell);
	return (shell->exit);
}

int	run_exec(t_myexec *exec, t_myshell *shell)
{
	if (check_syntax_cmd(&exec->parsing))
		return (2);
	if (parse_cmdtab(&exec->parsing, shell))
		return (1);
	if (build_cmdtab(&exec->cmdtab, &exec->parsing))
		return (1);
	return (run_cmdtab(&exec->cmdtab, exec->cmd_count, shell));
}
