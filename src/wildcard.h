/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:42:29 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 22:42:31 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../headers/minishell.h"
# include <dirent.h>

/*
 * is done is 0 if thers still wildcard in s
 * */
typedef struct s_wildcard {
	int					is_done;
	char				*s;
	struct s_wildcard	*next;
	struct s_wildcard	*child;
	struct s_wildcard	*parent;
}	t_wildcard;

typedef struct dirent	t_dirent;

char	*generate_wildcard(char *s, t_myenv *env);
void	wc_clean(t_wildcard **i);

#endif
