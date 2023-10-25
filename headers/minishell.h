/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+       */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/22 17:22:21 by nserve           ###   ########.fr       */
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
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include "../src/libft/libft.h"

# ifndef TEST_MODE
#  define TEST_STATIC static
# else
#  define TEST_STATIC
# endif

# define SYS_FAIL (-1)

extern volatile int	g_signal;

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

//----------------------------------------------------------------------------//

# define HISTORY_FILE ".inputrc"

typedef struct s_myentry {
	char				*content;
	struct s_myentry	*next;
}	t_myentry;

typedef t_myentry *		t_history;

int				entry_add(t_history *origin, char *str);
void			history_clean(t_history *history);
void			load_history(void);
void			register_history(t_history *history);

//----------------------------------------------------------------------------//

typedef struct s_myvar {
	char			*name;
	char			*value;
	struct s_myvar	*next;
	struct s_myvar	*prev;
}	t_myvar;

typedef t_myvar *		t_lstvar;

int				var_add(t_lstvar *origin, char *name, char *value);
void			var_update(t_myvar *var, char *name, char *value);
int				var_pop(t_lstvar *origin, t_myvar *var);
void			var_clean(t_lstvar *lst);
int				var_parsing(t_lstvar *lst, char *str);
t_lstvar		var_get(t_lstvar lst, char *name);
char			*var_get_value(t_lstvar lst, char *name);
char			*var_get_string(t_myvar *var);

//----------------------------------------------------------------------------//

typedef struct s_myenv {
	t_lstvar		lst_var;
	unsigned int	count;
	char			**envp;
	bool			subsh;
}	t_myenv;

int				env_init(t_myenv *env, char **envp);
int				env_update_count(t_myenv *env);
int				envp_update(t_myenv *env);
void			env_clean(t_myenv *env);
void			envp_clean(char ***envp);

//----------------------------------------------------------------------------//

# define EOF             (-1)
# define ERRCHAR         ( 0)
# define INIT_SRC_POS    (-2)
# define ENDLOOP         (-1)

typedef enum e_tok_type {
	TOK_INIT = -1,
	TOK_BRACKET = 0,
	TOK_WORD = 1,
	TOK_PIPE = 2,
	TOK_OR = 3,
	TOK_AND = 4,
	TOK_EOB = 5,
	TOK_EOF = 6,
	TOK_SYNTAX = 7,
}	t_tok_type;

typedef struct s_source {
	char		*buf;
	long		bufsize;
	long		curpos;
	char		*tok_buf;
	int			tok_bufsize;
	int			tok_bufindex;
	t_tok_type	tok_type;
}	t_source;

char			next_char(t_source *src);
void			unget_char(t_source *src);
char			peek_char(t_source *src);
void			skip_spaces(t_source *src);
int				source_init(t_source *src, char *cmdline);
void			source_clean(t_source *src);
void			tok_buf_reset(t_source *src);
void			tok_buf_add(t_source *src, char c);
void			tok_buf_pop(t_source *src);

typedef struct s_token {
	t_tok_type	type;
	t_source	*src;
	int			len;
	char		*txt;
}	t_token;

t_token			*token_word_new(char *str);
t_token			*token_ops_new(t_tok_type type);
void			token_clean(t_token *tok);
t_token			*tokenize(t_source *src);
void			untokenize(t_source *src);

//----------------------------------------------------------------------------//

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

int				glob_name(char name[256], char *prev, char *next);
int				wc_init(t_wildcard *wc, char *s);
int				wc_add(t_wildcard **origin, char *s);
void			wc_clean(t_wildcard **i);
int				wc_pregnant(t_wildcard *wc, t_dirent *elem);
int				wc_rec_expand(t_wildcard *wc);
int				wc_run_child(t_wildcard *wc);
char			*insert_name(t_wildcard *wc, char name[256]);
int				is_dir(t_wildcard *wc, t_dirent *elem);

typedef struct s_expand {
	char	*pstart;
	char	*p;
	bool	in_double_quote;
	bool	expanded;
}	t_expand;

int				expand_init(t_expand *expd, char *word);

//----------------------------------------------------------------------------//

typedef enum e_node_type {
	NODE_INIT = -1,
	NODE_BRACKET = 0,
	NODE_CMD = 1,
	NODE_PIPE = 2,
	NODE_OR = 3,
	NODE_AND = 4,
	NODE_WORD = 7,
}	t_node_type;

typedef enum e_redir_type {
	WORD = -1,
	READ,
	HEREDOC,
	TRUNC,
	APPEND,
}	t_redir_type;

typedef struct s_node {
	pid_t			pid;
	t_node_type		type;
	t_redir_type	rtype;
	int				fd[2];
	char			*val;
	int				exit;
	int				children;
	struct s_node	*parent;
	struct s_node	*first_child;
	struct s_node	*prev_sibling;
	struct s_node	*next_sibling;
}	t_node;

t_redir_type	find_word_type(char *data);
t_node			*node_new(t_node_type type);
t_node			*node_word_new(t_redir_type type);
t_node			*word_new(char *data);
int				node_val_set(t_node *node, char *val);
void			node_parent_add(t_node *child, t_node *parent);
void			node_parent_insert(t_node *parent, t_node *child);
void			node_child_add(t_node *parent, t_node *child);
void			node_tree_clean(t_node *node);
void			node_sibling_add(t_node **origin, t_node *child);
void			node_sibling_pop(t_node *node);
void			node_sibling_clean(t_node **origin);
void			word_pop(t_node **origin, t_node *word);

int				run_wildcard(t_node **word);

//----------------------------------------------------------------------------//

# define IN 0
# define OUT 1

typedef struct s_builtin {
	char	*name;
	int		(*f)(char **, t_myenv *);
}	t_builtin;

t_builtin		**builtin_init(void);
void			builtin_clean(t_builtin **builtins);

typedef struct s_execute {
	t_node	*bracket_first_child;
	int		(*builtin_f)(char **, t_myenv *);
	int		argc;
	int		argv_size;
	char	**argv;
	int		exit;
	int		std_fd[2];
	int		toclose_child;
}	t_execute;

int				check_argv_bounds(t_execute *exec);
int				add_to_argv(t_execute *exec, t_node *word);
void			exec_clean(t_execute *exec);

//----------------------------------------------------------------------------//

typedef struct s_myshell {
	t_history	hist;
	t_myenv		env;
	t_node		*root;
	int			exit;
}	t_myshell;

t_myshell		shell_init(void);
void			shell_clean(t_myshell *shell);

void			syntax_error_token(t_tok_type tok_type);
void			cmd_notfound(char *str);
void			path_notfound(void);

int				open_read(char *file);
int				open_append(char *file);
int				open_trunc(char *file);

void			close_redirection(t_node *cmd, int fd);

size_t			find_closing_quote(char *data);
size_t			find_closing_brace(char *data);

char			*ft_readline(char *prompt, void (*signal_handler)(int), 
				  void (*signal_restore));

#endif
