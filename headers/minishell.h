/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve & hmelica                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:41 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/10 14:59:17 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_MyVar {
  char  *name;
  char  *value;
  struct s_MyVar  next;
} t_MyVar;

typedef t_MyVar * t_LstVar

typedef struct s_MyEnv {
  t_LstVar          lst_var;
  struct s_MyVar    *pwd;
  struct s_MyVar    *oldpwd;
  struct s_MyVar    *home;
} t_MyEnv;

typedef struct s_MyHistory {
  char  *content;
  struct s_MyHistory  next;
} t_MyHistory;

typedef struct MyInput {
  
};

typedef struct s_MyParsing {
  enum lexer          type;
  char                *content;
  struct s_MyParsing  next;
} t_MyParsing;

typedef struct s_MyCmd
{
	pid_t			pid;
	int				in_fd;
	int				here_doc;
	char			*infile;
	char			*path;
	char			*args;
	char			*outfile;
	char			*wr_mode;
	int				out_fd;
}	t_MyCmd;

typedef struct MyExec {
  
};

typedef struct s_MyShell {
  struct s_MyHistory  history;
  struct s_MyEnv      env;
  struct s_MyInput    input;
  
  
} t_MyShell;


#endif
