/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:09 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:22:44 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "expander.h"
# include "scanner.h"

t_node	*choose_first_child(t_token *tok);
t_node	*insert_lvl_parent(t_node *parent, t_token *tok, int type);
t_node	*choose_lvl(t_node *parent, t_token *tok, int node_type);
t_node	*insert_lvl_child(t_node *parent, t_node *child);

t_node	*choose_lvl_bracket_error(t_node *parent, t_token *tok);
void	handle_error_lvl(t_node *parent, t_token *tok, int type);
void	handle_error_bracket(t_node *parent, t_token *tok);

void	parse_redir(t_token *tok, t_node *word);
t_node	*parse_word(t_token *tok);
t_node	*parse_command(t_token *tok);
t_node	*parse_bracket(t_token *tok);
t_node	*parse_lvl(t_node *parent, t_token *tok, int node_type);
int		parse_source(t_node **root, t_source *src);

#endif
