/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:15:53 by nserve            #+#    #+#             */
/*   Updated: 2023/10/15 18:15:56 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VAR_H
# define EXPAND_VAR_H

# include "../headers/minishell.h"

char *extract_value(char **line, int *i, t_lstvar lst);
void var_expansion(char **line, t_myenv *myenv);

#endif
