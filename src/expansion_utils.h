/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:09:38 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 19:09:41 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "../headers/minishell.h"

int		expand_init(t_expand *expd, char *word);
void	substitute_word();
t_node	*word_split(char *str);
t_node	*pathname_expand(t_node *args);
int		remove_quotes(t_node *args);

#endif
