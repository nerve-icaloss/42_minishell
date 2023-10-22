/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:33:58 by nserve            #+#    #+#             */
/*   Updated: 2023/10/15 17:34:00 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int	var_expansion(char **line, t_myenv *myenv);
t_node	*pathname_expansion(t_node *word);
int		remove_quotes(t_node *args);

t_node	*word_expansion(char *data, t_myenv *env);
t_node	*redir_expansion(char *data, t_redir_type type, t_myenv *env);

#endif
