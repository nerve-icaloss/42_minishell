/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:33:10 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:33:20 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PARSE_H
# define CMD_PARSE_H

# include "../headers/minishell.h"

int split_pipe_cmd(t_parsing *parsing, t_myshell *shell);
int extract_redir_in(t_parsing *parsing);
int extract_redir_out(t_parsing *parsing);
int expand_param(t_parsing *parsing, t_myshell *shell);
int split_word(t_parsing *parsing);

#endif
