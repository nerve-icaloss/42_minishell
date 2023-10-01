/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+     */
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

typedef int t_parsing; // DELETE THAT

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

t_myredir	*redir_init(void);
int			redirtab_init(t_redirtab *tab, int redir_count);
void		redirtab_clean(t_redirtab *tab);

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
int			cmdtab_init(t_cmdtab *tab, int cmd_count);
void		cmdtab_clean(t_cmdtab *tab);

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
# include <readline/history.h>

t_myentry	*new_entry(const char *str);
void		ft_add_history(t_history *history, t_myentry *new_entry);
void		ft_clear_history(t_history *history);
void		load_history(void);
void		register_history(t_history *history);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:11:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/01 14:25:09 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_insert
{
	char	type;
	int		flags;
	int		min_width;
	int		prec;
}	t_insert;

/* ft_is */
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_isplusminus(int c);
int			ft_isstr_int(char *str);

/* ft_to */
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
int			ft_atoi_base(char *str, char *base);
long		ft_atol(const char *str);
char		*ft_itoa(int n);

/* ft_mem */
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);

/* ft_trim */
char		*ft_trimleft(const char *str);
char		*ft_trimright(const char *str);

/* ft_str */
void		ft_arrclear(void **array);
size_t		ft_strlen(const char *s);
size_t		ft_wordlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strjoin2(char *s1, char *s2, int free_s1, int free_s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *s, const char *to_find, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		**ft_split(const char *s, char c);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ft_put */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ft_lst */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ft_printf and stuff */

int			ft_dprintf(int fd, const char *format, ...);
int			ft_printf(const char *format, ...);

int			check_flag(int nb, char c);
int			get_min_width(const char **format,
				int *flags, va_list act, va_list ori);
int			is_csp(char c);
int			is_digit(char c);
int			is_flag(char c);
int			set_flag(char c);
void		compile_flags(t_insert *ins);
int			precision(const char **format, va_list act, va_list ori);
int			read_following_int(const char **format);

int			display(char *s, t_insert ins, int force_len, int fd);
int			hex_len(unsigned long i);
int			int_len(unsigned int i);
void		dec_rec(unsigned int i, int fd);

int			main_c(va_list act, t_insert ins, int fd);
int			main_d(va_list act, t_insert ins, int fd);
int			main_p(va_list act, t_insert ins, int fd);
int			main_s(va_list act, t_insert ins, int fd);
int			main_u(va_list act, t_insert ins, int fd);
int			main_x(va_list act, t_insert ins, char *tab, int fd);

/* get_next_line */

typedef struct s_lstash
{
	char			buffer[BUFFER_SIZE + 1];
	size_t			buffersize;
	size_t			cumulsize;
	struct s_lstash	*next;
}	t_lstash;

// get_next_line_bonus.c
char		*get_next_line(int fd);
int			fill_lstash(int fd, t_lstash **p_lstash);
char		*build_nl(t_lstash **p_lstash);
void		copy_lstash(char *newline, t_lstash **p_lstash, size_t crlen);
t_lstash	*clean_lstash(t_lstash **p_lstash, size_t crlen);

// get_next_line_utils_bonus.c
size_t		nl_len(const char *str);
void		clear_lstash(t_lstash **stash);
void		add_lstash(t_lstash **lstash, t_lstash *newstash, size_t readsize);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:17:26 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 12:17:36 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDTAB_H
# define CMDTAB_H

# include "../headers/minishell.h"

int parse_cmdtab(t_parsing *parsing, t_myshell *shell);
int build_cmdtab(t_cmdtab *cmdtab, t_parsing *parsing);
int run_cmdtab(t_cmdtab *cmdtab, int cmd_count, t_myshell *shell);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syntax.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:39:51 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:40:01 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SYNTAX_H
# define CMD_SYNTAX_H

# include "../headers/minishell.h"

int check_syntax_cmd(t_parsing *parsing);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:33:10 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:33:20 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PARSE_H
# define CMD_PARSE_H

# include "../headers/minishell.h"

int split_pipe_cmd(t_parsing *parsing, t_myshell *shell);
int extract_redir_in(t_parsing *parsing);
int extract_redir_out(t_parsing *parsing);
int expand_param(t_parsing *parsing, t_myshell *shell);
int split_word(t_parsing *parsing);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:55:25 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 18:55:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_RUN_H
# define CMD_RUN_H

# include "../headers/minishell.h"

int single_cmd(t_mycmd *cmd, t_myshell *shell);
int single_builtin(t_mycmd *cmd, t_myshell *shell);
void single_child(t_mycmd *cmd, t_myshell *shell);
int single_parent(t_mycmd *cmd, t_myshell *shell);
void run_cmd(t_mycmd *cmd, t_myshell *shell);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:35:24 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:35:33 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILD_H
# define CMD_BUILD_H

# include "../headers/minishell.h"


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:54:08 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 18:54:16 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ERROR_H
# define CMD_ERROR_H

# include "../headers/minishell.h"

void cmd_notfound(char *s1);
void	path_notfound(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:56:10 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 12:56:18 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_REDIR_H
# define CMD_REDIR_H

# include "../headers/minishell.h"

int input_redirection(t_mycmd *cmd);
int output_redirection(t_mycmd *cmd);
int open_loop(t_redirtab *redirtab, int count);
void close_loop(t_redirtab *redirtab, int count);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:10:47 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 15:10:57 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_UTILS_H
# define VAR_UTILS_H

# include "../headers/minishell.h"

int var_parsing(t_lstvar *lst, char *str);
t_lstvar var_get(t_lstvar lst, char *name);
char *var_get_value(t_lstvar lst, char *name);
char *var_get_string(t_myvar *var);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:21:33 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 11:21:51 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

int open_read(char *file);
int open_append(char *file);
int open_trunc(char *file);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 09:44:00 by nserve            #+#    #+#             */
/*   Updated: 2023/09/30 09:44:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PIPE_H
# define CMD_PIPE_H

# include "../headers/minishell.h"

int	init_pipe(int **pipe_fd);
int open_pipe(t_cmdtab *cmdtab, int *pipe_fd[2], int cmd_count, int id);
int close_child_pipe(int pipe_fd[2], int cmd_id, int cmd_count);
int close_parent_pipe(t_cmdtab *cmdtab, int pipe_fd[2], int id, int count);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:54:41 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 12:54:50 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HEREDOC_H
# define CMD_HEREDOC_H

# include "../headers/minishell.h"

int heredoc_cmdtab(t_cmdtab *cmdtab, t_myshell *shell);
int heredoc_loop(t_redirtab *redirtab, t_myshell *shell);
int read_stdin(t_myredir *redir, t_myshell *shell);
void unlink_cmdtab(t_cmdtab *cmdtab);
void unlink_loop(t_redirtab *redirtab);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:22:36 by nserve            #+#    #+#             */
/*   Updated: 2023/09/26 17:22:39 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

# include "../headers/minishell.h"

int build_exectree(t_exectree *exectree, char *readline);
void clear_exectree(t_exectree *exectree);
int run_exectree(t_myshell *shell);
int parse_exec(t_parsing *parsing, t_myshell *shell);
int run_exec(t_myexec *exec, t_myshell *shell);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:13:52 by nserve            #+#    #+#             */
/*   Updated: 2023/09/28 17:15:25 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

# include "../headers/minishell.h"

int is_builtin(char *str);
int run_builtin(t_mycmd *cmd, t_myshell *shell);

int	unset_builtin(char **argv, t_lstvar *lst);
int	export_builtin(char **argv, t_myenv *env);
int	echo_builtin(char **argv);
int	env_builtin(t_myenv *env);
int	exit_builtin(char *argv[], t_myenv *env);
int	cd_builtin(char **argv, t_myenv *env);

#endif
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:29:54 by nserve            #+#    #+#             */
/*   Updated: 2023/09/27 10:30:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PIPEX_H
# define CMD_PIPEX_H

# include "../headers/minishell.h"

int pipex_cmd(t_cmdtab *cmd_tab, int cmd_count, t_myshell *shell);
void pipex_child(t_cmdtab *cmd_tab, int **pipe_fd, int cmd_id, t_myshell *shell);
int pipex_parent(t_cmdtab *cmd_tab, t_myshell *shell);

#endif
