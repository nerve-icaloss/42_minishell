/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:33:58 by nserve            #+#    #+#             */
/*   Updated: 2023/10/15 17:34:00 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H

# include "../headers/minishell.h"

t_node *new_word(char *data);
char *find_word(char *data);
void split_word(t_node **origin, char *data);
void find_expansion(t_expand *expd, t_myenv *env);
t_node *word_expansion(char *orig_arg, t_myenv *env);

#endif
