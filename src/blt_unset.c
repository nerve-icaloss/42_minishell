/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:26:12 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:09:11 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "utils_var.h"

/*
 * cannot fail in minishell
 * if not found, just goes to the next one
 * */
int	unset_builtin(char **argv, t_lstvar *lst)
{
	if (!argv || !*argv || !lst)
		return (-1);
	while (*++argv)
		var_pop(lst, var_get(*lst, *argv));
	return (0);
}
