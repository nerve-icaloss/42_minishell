/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:11:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/09/24 11:12:56 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 100

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_buffer
{
	char			*data;
	int				n;
	int				size;
	struct s_buffer	*last;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_insert
{
	char	type;
	int		flags;
	int		min_width;
	int		prec;
}	t_insert;

char			**ft_split(const char *str, char c);
char			**ft_split_e(const char *str, char c, char *b_set, char *e_set);
char			*ft_itoa(int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(char const *src);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strnstr(const char *big, const char *little,
					unsigned int len);
char			*ft_strrchr(char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(const char *s, unsigned int start, unsigned int len);
char			*ft_strchr(const char *s, int c);
char			*get_next_line(int fd);
int				ft_atoi(const char *str);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_lstsize(t_list *lst);
int				ft_memcmp(const void *s1, const void *s2, unsigned int n);
int				ft_printf(const char *format, ...);
int				ft_strlen(char const *str);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_tolower(int c);
int				ft_toupper(int c);
long			ft_atol(const char *str);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
t_list			*ft_lstnew(void *content);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
void			*ft_calloc(unsigned int nmemb, unsigned int size);
void			*ft_memchr(const void *s, int c, unsigned int n);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			*ft_memset(void *s, int c, unsigned int n);
void			ft_bzero(void *s, unsigned int n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

char			*treatment(t_buffer **b);
t_buffer		*buffer_clean(t_buffer **b);
t_buffer		*buffer_new(t_buffer **b);
t_buffer		*buffer_remove(t_buffer *b);
void			copypaste(t_buffer **b, char **ret, int len);

int				check_flag(int nb, char c);
int				get_min_width(const char **format,
					int *flags, va_list act, va_list ori);
int				is_csp(char c);
int				is_digit(char c);
int				is_flag(char c);
int				set_flag(char c);
void			compile_flags(t_insert *ins);
int				precision(const char **format, va_list act, va_list ori);
int				read_following_int(const char **format);

int				display(char *s, t_insert ins, int force_len, int fd);
int				hex_len(unsigned long i);
int				int_len(unsigned int i);
void			dec_rec(unsigned int i, int fd);

int				main_c(va_list act, t_insert ins, int fd);
int				main_d(va_list act, t_insert ins, int fd);
int				main_p(va_list act, t_insert ins, int fd);
int				main_s(va_list act, t_insert ins, int fd);
int				main_u(va_list act, t_insert ins, int fd);
int				main_x(va_list act, t_insert ins, char *tab, int fd);

#endif
