/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:22:36 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:22:39 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

# include "../headers/minishell.h"

int build_exectree(t_exectree *exectree, char *readline);
void clear_exectree(t_exectree *exectree);
int run_exectree(t_myshell *shell);
int parse_exec(t_parsing *parsing, t_myshell *shell);
int run_exec(t_myexec *exec, t_myshell *shell);

#endif
