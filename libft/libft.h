/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:21:31 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/09 21:24:21 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
	Libraries required
*/
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

/*
	Struct
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*
	Prototypes
*/
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *));

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_itoa_unsigned(unsigned int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int i, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memalloc(size_t size);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnew(size_t size);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strmap(char const *s, char (*f)(char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_striter(char *s, void (*f)(char *));
int				ft_strequ(char const *s1, char const *s2);
void			ft_strdel(char **as);
char			*ft_strcpy(char *dst, const char *src);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcat(char *s1, const char *s2);
void			ft_strclr(char *s);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);
void			ft_putendl(char const *s);
void			ft_putchar(char c);
void			ft_memdel(void **ap);
char			*ft_strjoin_size(char const *s1, char const *s2, int size_s2);
int				get_next_line(const int fd, char **line);
char			*ft_strtrim_path(char const *s1, char const *set);
char			**ft_split_str(char *str, char *charset);
float			ft_abs(float nb);
int				ft_strslen(char **strs);
char	*ft_strnew(size_t size);

#endif
