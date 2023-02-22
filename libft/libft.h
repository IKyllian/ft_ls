/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:56:24 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 10:56:21 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define MAX(a, b)	b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)	a & ((a - b) >> 31) | b & (~(a - b) >> 31)

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_struct
{
	int			has_neg;
	int			has_zero;
	int			len_field;
	int			len_is_neg;
	int			has_dot;
	int			dot_val;
	int			has_star;
	int			neg_print;
	char		type;
}				t_flags;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					integer_length(long nbr);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				*ft_memset(void *s, int c, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t size);
void				*ft_memccpy(void *dst, const void *src, int ch, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strdup(const char *source);
void				*ft_calloc(size_t element_count, size_t element_size);
char				*ft_itoa(int n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int				ft_printf(const char *format, ...);
void			ft_putchar(char c, int *count);
void			ft_putnbr(int n, int *count);
void			ft_unsigned_putnbr(unsigned long long n, int *count);
void			ft_putstr(char *str, int *count);
void			fill_space(char c, int size, int *count);
int				ft_itoh(unsigned long long nb, int low, int *ct, t_flags *flg);
// int				nbr_length(int nbr);
int				u_nbr_len(unsigned long long nbr, unsigned int size_base);

int				is_flags(char c);
int				ft_count_numbers(char **str);
int				ft_convert(char **str, va_list list, int *count, t_flags *flag);
void			struct_initialize(t_flags *flags);
void			check_space_is_neg(t_flags *flags);
void			to_decimal(va_list list, int *count, t_flags *flags);
void			to_unsigned_decimal(va_list list, int *count, t_flags *flags);
int				to_hexa(va_list list, int *count, int is_min, t_flags *flags);
void			to_character(va_list list, int *count, t_flags *flags);
int				to_pointer_address(va_list list, int *count, t_flags *flags);
void			to_string(va_list list, int *count, t_flags flags);
void			to_percent(int *count, t_flags *flags);

void			ope_dot_address(t_flags *f, int *count, int arg, int *len);
void			ope_dot(t_flags *f, int *count, int arg, int *len);
void			ope_space(t_flags *flags, int *c, int arg, int *len);
void			ope_space_suff(t_flags *flags, int *count, int arg, int len);
void			print_neg(int arg, int *count, t_flags *flags, int *arg_len);

void			operands_string_dot(t_flags flags, int *count, int len);
void			ope_space_string(t_flags flags, int *count, int len);
void			ope_space_string_suff(t_flags flags, int *count, int len);
void			print_string(t_flags flags, int *count, char *str, int len);

#endif
