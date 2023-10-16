/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:45:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/16 09:45:36 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_EXPANSION_H
# define REDIR_EXPANSION_H

# include "../headers/minishell.h"

t_node *new_redir(char *data, t_redir_type type);
t_node *redir_expansion(char *data, t_redir_type type, t_myenv *env);

#endif
