/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:45:08 by nserve            #+#    #+#             */
/*   Updated: 2023/09/15 13:59:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "../headers/minishell.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

t_myentry	*new_entry(const char *str);
void		ft_add_history(t_myhistory *history, t_myentry *new_entry);
void		ft_clear_history(t_myhistory *history);
void		load_history(void);
void		register_history(t_myhistory *history);

#endif
