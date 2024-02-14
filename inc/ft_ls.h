/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:01 by kdelport          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#ifdef __APPLE__
#ifndef st_mtime
# define st_mtime st_mtimespec.tv_sec
#endif
#endif

#ifdef __APPLE__
#ifndef st_atime
# define st_atime st_atimespec.tv_sec
#endif
#endif

#ifdef __APPLE__
#ifndef st_ctime
# define st_ctime st_ctimespec.tv_sec
#endif
#endif

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <grp.h>
# include <string.h>
# include <time.h>
# include <limits.h>
# include <pwd.h>
# include <errno.h>
# include "libft.h"

# define SIZE_LENGTH 4
# define SIZE_PERM 12

# define COLOR_DEFAULT	"\033[0m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_PURPLE	"\033[0;35m"

typedef struct s_options
{
	int	reverse;
	int	sort_time;
	int	show_hidden;
	int	long_format;
	int	list_subdir;
}	t_options;

typedef struct s_subDir_infos
{
	int		is_sub_dir;
	int		is_first_dir;
	char	*init_path;
}			t_subDir_infos;

typedef struct s_dirInfos
{
	struct stat			dir_stat;
	char				*dir_name;
	char				*path;
	char				*owner;
	char				*gr_name;
	int					is_sub_dir;
	int					is_file;
	blkcnt_t			blocks_size;
	struct s_dirInfos	*sub_dir;
	struct s_dirInfos	*next;
}						t_dirInfos;

typedef struct s_arg_list
{
	struct stat			dir_stat;
	char				*dir_name;
	int					is_file;
	struct s_arg_list	*next;
}				t_arg_list;

typedef struct s_heads_list
{
	t_dirInfos	*list;
	t_dirInfos	*ret;
	t_dirInfos	*dir_parent;
}				t_heads_list;

typedef struct s_datas
{
	t_options	options;
	int			size[SIZE_LENGTH];
	int			error;
}	t_datas;

int				char_is_flag(char c);
void			fill_options(char c, t_options *options);
int				is_untrack_folder(char *str);
int				is_hidden_folder(char *str);
int				max_nbr(int a, int b);

void			free_lst_item(t_dirInfos **item);
void			free_arg_list(t_arg_list **arg_list);
void			free_lst(t_dirInfos **dirList);
t_dirInfos		*dir_error(t_dirInfos **head, char *ptr, t_datas *datas);

void			set_permision(struct stat dir_stat, char str[SIZE_PERM]);
char			set_file_type(mode_t mode);
void			set_column_size(int size[SIZE_LENGTH], t_dirInfos *dir);

void			print_long_format(t_dirInfos *dir, int size[SIZE_LENGTH]);
void			print_date(t_dirInfos *dir, char *dir_time);
void			dir_infos_manager(t_dirInfos **dirList, t_datas *datas, \
	int isSub);
char			get_file_attributes(t_dirInfos *dir);

void			main_struct_init(t_datas *datas);
t_dirInfos		*init_dir_info(char dir_name[256], char *path, int is_sub_dir);
t_subDir_infos	init_sub_dir_infos(int is_sub_dir);
t_heads_list	init_heads_list(t_dirInfos **dirList);
int				dup_strings(t_dirInfos **new, char dir_name[256], \
	struct stat dir_stat, char *path);
t_dirInfos		*init_for_file(char *path);

t_arg_list		*create_arg(char *arg, int is_file);
t_arg_list		*add_sort(t_arg_list **list, t_arg_list **last, \
	t_arg_list **begin, t_arg_list **new);
t_arg_list		*add_arg(char *path, int is_file, t_arg_list **arg_list, \
	t_options options);

t_dirInfos		*ft_lstadd_first(t_datas *datas, t_heads_list *heads_list, \
	t_dirInfos **new, t_subDir_infos *subDirInfos);
t_dirInfos		*ft_lstadd_second(t_dirInfos **new, t_heads_list *heads_list, \
	t_options	options);

t_arg_list		*parser(char **av, int ac, t_options *options);

t_dirInfos		*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList);

int				sort_by_letter(t_dirInfos *new, t_dirInfos *list, int reverse);
int				sort_by_time(t_dirInfos *new, t_dirInfos *list, \
	t_options options);
int				sort_arg_by_time(t_arg_list *new, t_arg_list *list, \
	t_options options);
int				sort_arg_by_letter(t_arg_list *new, t_arg_list \
	*list, int reverse);

t_dirInfos		*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList);
t_dirInfos		*browse_dir(t_datas *datas, DIR **p_dir, t_dirInfos **dirList, \
	t_subDir_infos *sub_dir_infos);
int				skip_dir(DIR **p_dir, struct dirent **currt_dir, \
	t_datas *datas);
t_dirInfos		*fill_variable(t_subDir_infos *sub_dir_infos, \
	struct dirent *current_dir, char **str);

char			*join_path(char *path);
t_dirInfos		*create_file(char **init_path, char *path);
int				skip_dir(DIR **p_dir, struct dirent **currt_dir, \
	t_datas *datas);
void			loop_end(char **str, struct dirent **currt_dir, DIR **p_dir);

#endif