/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:54:41 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 12:54:50 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HEREDOC_H
# define CMD_HEREDOC_H

# include "../headers/minishell.h"

int heredoc_cmdtab(t_cmdtab *cmdtab, t_myshell *shell);
int heredoc_loop(t_redirtab *redirtab, t_myshell *shell);
int read_stdin(t_myredir *redir, t_myshell *shell);
void unlink_cmdtab(t_cmdtab *cmdtab);
void unlink_loop(t_redirtab *redirtab);

#endif
