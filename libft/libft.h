/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:18 by gguardam          #+#    #+#             */
/*   Updated: 2026/09/18 16:13:25 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
char	*ft_itoa(int num);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *c, int fd);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
long	ft_atol(const char *str);
char	*ft_free_gnl(char **str);
char	*ft_extract_line(char *stash);
char	*ft_update_line(char *stash);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *stash, char *str);
size_t	ft_strlen_gnl(char *s);
char	*ft_substr_gnl(char *stash, unsigned int start, size_t len);
char	*ft_strchr_gnl(char *stash, char c);
int		ft_fprint_char(int fd, int c);
int		ft_fprint_hex_bottom(int fd, unsigned long long num);
int		ft_fprint_hex_top(int fd, unsigned int num);
int		ft_fprint_specifier(int fd, char specifier, va_list input);
int		ft_fprintf(int fd, char const *chain, ...);
int		ft_fprint_nbr(int fd, int num);
int		ft_fprint_ptr(int fd, void *ptr);
int		ft_fprint_str(int fd, char *str);
int		ft_fprint_uns(int fd, unsigned int num);


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);

#endif