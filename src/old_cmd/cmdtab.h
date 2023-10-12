/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:17:26 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 12:17:36 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDTAB_H
# define CMDTAB_H

# include "../headers/minishell.h"

int parse_cmdtab(t_parsing *parsing, t_myshell *shell);
int build_cmdtab(t_cmdtab *cmdtab, t_parsing *parsing);
int run_cmdtab(t_cmdtab *cmdtab, int cmd_count, t_myshell *shell);

#endif
