/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:03:53 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 12:03:56 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdtab.h"
#include "cmdtab_parse.h"
#include "cmdtab_build.h"
#include "cmd_run.h"
#include "cmd_pipex.h"

int	parse_cmdtab(t_parsing *parsing, t_myshell *shell)
{
	if (split_pipe_cmd(parsing, shell))
		return (1);
	if (extract_redir_in(parsing))
		return (1);
	if (extract_redir_out(parsing))
		return (1);
	if (expand_param(parsing, shell))
		return (1);
	if (split_word(parsing))
		return (1);
	return (0);

}

int	build_cmdtab(t_cmdtab *cmdtab, t_parsing *parsing)
{
	return (0);
}

int	run_cmdtab(t_cmdtab *cmdtab, int cmd_count, t_myshell *shell)
{
	if (cmd_count == 1)
		return (single_cmd(cmdtab[0], shell));
	else
		return (pipex_cmd(cmdtab, cmd_count, shell));
}

