/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:09 by nserve            #+#    #+#             */
/*   Updated: 2023/10/10 18:24:13 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../headers/minishell.h"

t_node *parse_word(t_token *tok, t_myenv *env);
t_node *parse_command(t_token *tok, t_myenv *env);
t_node	*parse_bracket(t_token *tok, t_myenv *env);
t_node *parse_lvl(t_node *parent, t_token *tok, int node_type, t_myenv *env);
int parse_source(t_node **root, t_source *src, t_myenv *env);

#endif
