/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:53:55 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/19 18:40:04 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef INT_MIN
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* DYNAMIC ALLOCATION - Memory management functions */
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* CHARACTER OPERATIONS - Character classification and conversion */
int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* STRING OPERATIONS - String manipulation and analysis */
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/* MEMORY OPERATIONS - Memory manipulation and comparison */
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* FILE DESCRIPTOR OPERATIONS - Output to file descriptors */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* NUMBER CONVERSION - Integer to string conversion */
char	*ft_itoa(int n);

/* STRING CONVERSION - String to number conversion */
int		ft_atoi(const char *nptr);
double	ft_atof(char *str);

/* PRINTF */
int		ft_printf(const char *format, ...);
int		base_len(char *base);
int		ft_putchar(char c, int fd);
int		ft_putstr(char *str, int fd);
int		ft_putnbr(int n, int fd);
int		ft_putnbr_u(unsigned int n);
int		ft_putnbr_hex(unsigned int nbr, char *base);
int		ft_putadress(void *nbr, char *base);
int		ft_putnbr_base_ul(unsigned long long nbr, char *base);
int		ft_putnbr_float(double n, int precision, int fd);

/* GNL */
char	*get_next_line(int fd);

#endif
