/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:33:58 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:20:09 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int		var_expansion(char **line, t_myenv *myenv);
t_node	*pathname_expansion(t_node *word);
int		remove_quotes(t_node *args);
int		remove_quotes_str(char **str);

t_node	*word_expand(char *data, t_myenv *env);
char	*redir_expand(char *data, t_redir_type type, t_myenv *env);

#endif
