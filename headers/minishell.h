/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+       */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 16:33:41 by hmelica          ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../src/libft/libft.h"

# define SYS_FAIL (-1)

//----------------------------------------------------------------------------//

# define HISTORY_FILE ".inputrc"

typedef struct s_myentry {
	char				*content;
	struct s_myentry	*next;
}	t_myentry;

typedef t_myentry *	t_history;

int			entry_add(t_history *origin, char *str);
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
void		var_update(t_myvar *var, char *name, char *value);
int			var_pop(t_lstvar *origin, t_myvar *var);
void		var_clean(t_lstvar *lst);
int			var_parsing(t_lstvar *lst, char *str);
t_lstvar	var_get(t_lstvar lst, char *name);
char		*var_get_value(t_lstvar lst, char *name);
char		*var_get_string(t_myvar *var);

//----------------------------------------------------------------------------//

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

int			env_init(t_myenv *env, char **envp);
int			env_update_count(t_myenv *env);
int			envp_update(t_myenv *env);
void		env_clean(t_myenv *env);
void		envp_clean(char ***envp);

//----------------------------------------------------------------------------//

# define EOF             (-1)
# define ERRCHAR         ( 0)
# define INIT_SRC_POS    (-2)
# define ENDLOOP         (-1)

typedef enum e_tok_type {
	TOK_BRACKET = 0,
	TOK_WORD = 1,
	TOK_PIPE = 2,
	TOK_OR = 3,
	TOK_AND = 4,
	TOK_EOB = 5,
	TOK_EOF = 6,
	TOK_SYNTAX = 7,
}	t_tok_type;

typedef struct s_source
{
    char		*buf;       /* the input text */
    long		bufsize;       /* size of the input text */
    long		curpos;       /* absolute char position in source */
    char		*tok_buf;
    int			tok_bufsize;
    int			tok_bufindex;
    t_tok_type	tok_type;
}	t_source;

char		next_char(t_source *src);
void		unget_char(t_source *src);
char		peek_char(t_source *src);
void		skip_spaces(t_source *src);
int			tok_buf_init(t_source *src);
void		tok_buf_reset(t_source *src);
void		tok_buf_add(t_source *src, char c);

typedef struct s_token {
	t_tok_type	type;
	t_source	*src;
	int			len;
	char		*txt;
}	t_token;

t_token		*token_word_new(char *str);
t_token		*token_ops_new(t_tok_type type);
void		token_clean(t_token *tok);
t_token		*tokenize(t_source *src);
void		untokenize(t_source *src);

//----------------------------------------------------------------------------//

typedef enum e_node_type {
	NODE_BRACKET = 0,
	NODE_CMD = 1,
	NODE_PIPE = 2,
	NODE_OR = 3,
	NODE_AND = 4,
	NODE_IN = 5,
	NODE_OUT = 6,
	NODE_VAR = 7,
}	t_node_type;

typedef struct s_node {
	t_node_type		type;
	int				in_fd;
	int				out_fd;
	char			*val;
	int				exit;
	int				children;
	struct s_node	*parent;
	struct s_node	*first_child;
	struct s_node	*prev_sibling;
	struct s_node	*next_sibling;
}	t_node;

t_node		*node_new(t_node_type type);
int			node_val_set(t_node *node, char *val);
void		node_parent_add(t_node *child, t_node *parent);
void		node_last_retrieve(t_node *parent, t_node *child);
void		node_child_add(t_node *parent, t_node *child);
void		node_tree_clean(t_node *node);

//----------------------------------------------------------------------------//

typedef struct s_myshell {
	t_history	hist;
	t_myenv		env;
	t_node		*root;
	int			exit;
}	t_myshell;

t_myshell	shell_init();
void		shell_clean(t_myshell *shell);

#endif


