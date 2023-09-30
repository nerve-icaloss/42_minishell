/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:13:52 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 17:15:25 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

# include "../headers/minishell.h"
//# include "blt_cd.h"
//# include "blt_pwd.h"
//# include "blt_env.h"
//# include "blt_export.h"
//# include "blt_unset.h"
# include "blt_exit.h"

int is_builtin(char *str);
int run_builtin(t_mycmd *cmd, t_myshell *shell);

#endif
