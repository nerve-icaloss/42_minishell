/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:45:08 by nserve            #+#    #+#             */
/*   Updated: 2023/09/14 18:46:05 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "../headers/minishell.h"

void ft_add_history(t_myshell *shell);
void ft_clear_history(t_myshell *shell);
void load_history(t_myshell *shell);
void save_history(t_myshell *shell);

#endif
