/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:59 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 11:46:35 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENH_H
# define ENV_H

# include "minishell.h"

// var.c
int		var_add(t_lstvar *origin, char *name, char *value);
int		var_parsing(t_lstvar *lst, char *str);
void	var_clean(t_lstvar *lst);

#endif
