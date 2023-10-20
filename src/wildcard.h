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
	char				*path;
	char				*glob_prev;
	char				*wc;
	char				*glob_next;
	char				*following;
	char				*s;
	struct s_wildcard	*next;
	struct s_wildcard	*child;
	struct s_wildcard	*parent;
}	t_wildcard;

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

char	*generate_wildcard(char *s);

int		wc_add(t_wildcard **origin, char *s);
void	wc_clean(t_wildcard **i);
char	*wc_to_str(t_wildcard *wc);
char	*insert_name(t_wildcard *wc, char name[256]);

int		glob_name(char name[256], char *prev, char *next);
int		is_dir(t_wildcard *wc, t_dirent *elem);

#endif
