/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:46:53 by nserve            #+#    #+#             */
/*   Updated: 2023/10/15 09:46:56 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_UTILS_H
# define FIND_UTILS_H

# include "../headers/minishell.h"

t_redir_type find_word_type(char *data);
void	find_expansion(t_expand *expd, t_myenv *env);
size_t find_closing_quote(char *data);
size_t find_closing_brace(char *data);

#endif
