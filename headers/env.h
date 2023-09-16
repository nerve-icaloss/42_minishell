/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:33:59 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:31 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENH_H
# define ENV_H

# include "minishell.h"

// env.c
int			env_init(t_myenv *myenv, char **envp);
int			env_builtin(t_myenv *myenv);
void		env_clean(t_myenv *myenv);
int			env_update_count(t_myenv *myenv);

// envp.c
void		envp_clean(char ***envp);
int			envp_update(t_myenv *myenv);

// var.c
char		*var_get_string(t_lstvar var);
char		*var_get_value(t_lstvar lst, char *name);
int			var_parsing(t_lstvar *lst, char *str);
t_lstvar	var_get(t_lstvar lst, char *name);

// var_utils.c
int			var_add(t_lstvar *origin, char *name, char *value);
void		var_clean(t_lstvar *lst);

#endif
