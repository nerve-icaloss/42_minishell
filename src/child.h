/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:15:32 by nserve            #+#    #+#             */
/*   Updated: 2023/10/17 18:15:35 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "../headers/minishell.h"

void child_cmd(t_execute *exec, t_myshell *shell);
void child_pipex_cmd(t_execute *exec, t_myshell *shell);

#endif
