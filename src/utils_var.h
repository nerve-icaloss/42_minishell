/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:10:47 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 15:10:57 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_UTILS_H
# define VAR_UTILS_H

# include "../headers/minishell.h"

int			var_parsing(t_lstvar *lst, char *str);
t_lstvar	var_get(t_lstvar lst, char *name);
char		*var_get_value(t_lstvar lst, char *name);
char		*var_get_string(t_myvar *var);
int			env_update_count(t_myenv *env);

#endif
