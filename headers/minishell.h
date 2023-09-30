/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/15 14:31:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../src/libft/libft.h"

# define SYS_FAIL -1
# define HISTORY_FILE ".inputrc"

//----------------------------------------------------------------------------//

typedef struct s_myentry {
	const char			*content;
	struct s_myentry	*next;
}	t_myentry;

typedef t_myentry *	t_history;

t_myentry *new_entry(const char *str);
void add_entry(t_history *history, t_myentry *entry);
void clean_history(t_history *history);

//----------------------------------------------------------------------------//

typedef struct s_myvar {
	char			*name;
	char			*value;
	struct s_myvar	*next;
	struct s_myvar	*prev;
}	t_myvar;

typedef t_myvar *	t_lstvar;

typedef struct s_myenv {
	t_lstvar		lst_var;
	unsigned int	count;
	char			**envp;
	struct s_myvar	*pwd;
	struct s_myvar	*oldpwd;
	struct s_myvar	*home;
	struct s_myvar	*path;
	struct s_myvar	*shlvl;
}	t_myenv;

//----------------------------------------------------------------------------//

typedef enum e_lexer {
	input = 1,
	cmd,
	redir_in,
	redir_out,
	name,
	//flags
	args,
}	t_lexer;

typedef struct s_myelement {
	struct s_myelement	*prev;
	int					cmd_id;
	t_lexer				type;
	int					pos;
	char				*content;
	struct s_myelement	*next;
}	t_myelement;

typedef t_myelement *	t_parsing;

t_myelement *new_element(char *input, t_lexer type);
void addtop_element(t_parsing *parsing, t_myelement *element);
void addbot_element(t_parsing *parsing, t_myelement *element);
void insert_element(t_parsing *parsing, t_myelement *element);
void clean_parsing(t_parsing *parsing);

//----------------------------------------------------------------------------//

typedef enum e_symbol {
	o_read = 60,
	o_doc = 6060,
	o_trunc = 62,
	o_append = 6262,
}	t_symbol;

typedef struct s_myredir {
	t_symbol	redir;
	char		*limiter;
	bool		expand;
	int			fd;
	char		*file;
} t_myredir;

typedef t_myredir *	t_redirtab;

t_myredir *new_redir();
t_redirtab *new_redirtab();
void clean_redirtab(t_redirtab *redirtab);

//----------------------------------------------------------------------------//

typedef struct s_mycmd
{
	pid_t		pid;
	int			in_count;
	t_redirtab	in;
	int			in_fd;
	char		*path; //exec_path
	char		*name;
	char		**args;
	int			out_fd;
	int			out_count;
	t_redirtab	out;
}	t_mycmd;

typedef	t_mycmd *	t_cmdtab;

t_mycmd *new_cmd();
t_cmdtab *new_cmdtab();
void clean_cmdtab(t_cmdtab *cmdtab);

//----------------------------------------------------------------------------//

typedef struct s_myexec {
	pid_t			pid;
	char			*input;
	t_parsing		parsing;
	int				cmd_count;
	t_cmdtab		cmdtab;
	int				exit;
	struct s_myexec	*left;
	struct s_myexec	*right;
}	t_myexec;

typedef t_myexec *	t_exectree;

t_myexec *new_exec(char *input);
void add_exec_left(t_exectree *exectree, t_myexec *exec);
void add_exec_right(t_exectree *exectree, t_myexec *exec);
void clean_exectree(t_exectree *exectree);

//----------------------------------------------------------------------------//

typedef struct s_myshell {
	t_history	history;
	t_myenv		env;
	char		*readline;
	t_exectree	exectree;
	int			exit;
}	t_myshell;

t_myshell new_shell();
void clean_shell(t_myshell *shell);

#endif
