/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_search.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:50:15 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 16:50:23 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SEARCH_H
# define CMD_SEARCH_H

# include "../headers/minishell.h"

char *get_cmd_path(char *name, t_myshell *shell);
char *find_cmd_path(char *name, char *paths[]);

#endif
