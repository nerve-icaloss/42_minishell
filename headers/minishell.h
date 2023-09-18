/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 14:31:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>

# define HISTORY_FILE "minishell_history.log"

typedef struct s_myvar {
	char			*name;
	char			*value;
	struct s_myvar	*next;
}	t_myvar;

typedef t_myvar *	t_lstvar;

typedef struct s_myenv {
	t_lstvar		lst_var;
	char			**envp;
	t_myvar	*pwd;
	t_myvar	*oldpwd;
	t_myvar	*home;
}	t_myenv;

typedef struct s_myentry {
	const char			*content;
	struct s_myentry	*next;
}	t_myentry;

typedef t_myentry *	t_myhistory;

typedef struct s_myinput {
	char	*content;
}	t_myinput;

typedef enum e_lexer {
	in=1,
	cmd,
	redir,
	arg,
}	t_lexer;

typedef struct s_myparsing {
	enum e_lexer		type;
	char				*content;
	struct s_myparsing	*next;
} t_myparsing;

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

typedef struct s_myexec {
	
}	t_myexec;

typedef struct s_myshell {
	t_myhistory	history;
	t_myenv		*env;
	t_myinput	input;
	t_myparsing	*parsing;
	t_myexec	*exec;
}	t_myshell;

#endif
