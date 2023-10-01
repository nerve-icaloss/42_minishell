/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 09:33:16 by hmelica          ###   ########.fr       */
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
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SYS_FAIL -1
# define HISTORY_FILE ".inputrc"
# include "../src/libft/libft.h"

//----------------------------------------------------------------------------//

typedef struct s_myentry {
	const char			*content;
	struct s_myentry	*next;
}	t_myentry;

typedef t_myentry *	t_history;

t_myentry	*entry_init(const char *str);
void		entry_add(t_history *history, t_myentry *entry);
void		history_clean(t_history *history);

//----------------------------------------------------------------------------//

typedef struct s_myvar {
	char			*name;
	char			*value;
	struct s_myvar	*next;
	struct s_myvar	*prev;
}	t_myvar;

typedef t_myvar *	t_lstvar;

int			var_add(t_lstvar *origin, char *name, char *value);
int			var_pop(t_lstvar *origin, t_myvar *var);
void		var_update(t_myvar *var, char *name, char *value);
void		var_clean(t_lstvar *lst);


typedef struct s_myenv {
	t_lstvar		lst_var;
	unsigned int	count;
	char			**envp;
	struct s_myvar	*pwd;
	struct s_myvar	*oldpwd;
	struct s_myvar	*home;
	struct s_myvar	*path;
	struct s_myvar	*shlvl;
	bool			subsh;
}	t_myenv;

int			envp_update(t_myenv *env);
void		envp_clean(char ***envp);
int			env_init(t_myenv *env, char **envp);
void		env_clean(t_myenv *env);

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

typedef struct s_mytoken {
	struct s_myelement	*prev;
	int					cmd_id;
	t_lexer				type;
	int					pos;
	char				*content;
	struct s_mytoken	*next;
}	t_mytoken;

typedef t_mytoken *	t_tokentree;

t_mytoken	*token_init(char *str, t_lexer type);
void		token_addleft(t_tokentree *tokentree, t_mytoken *token);
void		token_addright(t_tokentree *tokentree, t_mytoken *token);
void		token_insert(t_tokentree *tokentree, t_mytoken *token);
void		tokentree_clean(t_tokentree *tokentree);

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
}	t_myredir;

typedef t_myredir *	t_redirtab;

t_myredir	*redir_init();
t_redirtab	*redirtab_init();
void		redirtab_clean(t_redirtab *redirtab);

//----------------------------------------------------------------------------//

typedef struct s_mycmd
{
	pid_t		pid;
	int			in_count;
	t_redirtab	in;
	int			in_fd;
	char		*path;
	char		*name;
	char		**args;
	int			out_fd;
	int			out_count;
	t_redirtab	out;
}	t_mycmd;

typedef	t_mycmd *	t_cmdtab;

t_mycmd		*cmd_init(void);
t_cmdtab	*cmdtab_init(int cmd_count);
void		cmdtab_clean(t_cmdtab *cmdtab);

//----------------------------------------------------------------------------//

typedef struct s_myexec {
	pid_t			pid;
	char			*input;
	t_tokentree		parsing;
	int				cmd_count;
	t_cmdtab		cmdtab;
	int				exit;
	struct s_myexec	*left;
	struct s_myexec	*right;
}	t_myexec;

typedef t_myexec *	t_exectree;

t_myexec	*exec_init(char *input);
void		exec_addleft(t_exectree *exectree, t_myexec *exec);
void		exec_addright(t_exectree *exectree, t_myexec *exec);
void		exectree_clean(t_exectree *exectree);

//----------------------------------------------------------------------------//

typedef struct s_myshell {
	t_history	history;
	t_myenv		env;
	char		*readline;
	t_exectree	exectree;
	int			exit;
}	t_myshell;

t_myshell	shell_init();
void		shell_clean(t_myshell *shell);

#endif
