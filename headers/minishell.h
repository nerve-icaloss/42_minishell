/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/14 11:13:22 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_myvar {
	char			*name;
	char			*value;
	struct s_myvar	*next;
	struct s_myvar	*prev;
}	t_myvar;

typedef t_myvar *	t_lstvar;

typedef struct s_myenv {
	t_lstvar		lst_var;
	struct s_myvar	*pwd;
	struct s_myvar	*oldpwd;
	struct s_myvar	*home;
}	t_myenv;

typedef struct s_myhistory {
	char				*content;
	struct s_myhistory	next;
} t_myhistory;

typedef struct myinput {
	
};

typedef struct s_myparsing {
	enum lexer			type;
	char				*content;
	struct s_myparsing	next;
} t_MyParsing;

typedef struct s_mycmd
{
	pid_t	pid;
	int		in_fd;
	int		here_doc;
	char	*infile;
	char	*path;
	char	*args;
	char	*outfile;
	char	*wr_mode;
	int		out_fd;
}	t_mycmd;

/*
typedef struct myexec {
	
};

typedef struct s_myshell {
	struct s_myhistory	history;
	struct s_myenv			env;
	struct s_myinput		input;
	
	
} t_myshell;
*/

#endif
