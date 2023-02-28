/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:01 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/28 10:35:20 by kdelport         ###   ########.fr       */
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
# include <pwd.h>
# include "../libft/libft.h"

# define SIZE_LENGTH 4
# define SIZE_PERM 11

# define COLOR_DEFAULT	"\033[0m"
# define COLOR_CYAN		"\033[1;36m"

typedef struct s_options {
	int	reverse;
	int	sort_time;
	int	show_hidden;
	int	long_format;
	int	list_subdir;
}	t_options;

typedef struct s_subDir_infos {
	int		is_sub_dir;
	int		is_first_dir;
	char	*init_path;
}			t_subDir_infos;

typedef struct s_dirInfos {
	struct stat			dir_stat;
	char				*dir_name;
	char				*path;
	char				*owner;
	char				*gr_name;
	int					is_sub_dir;
	blkcnt_t			blocks_size;
	struct s_dirInfos	*sub_dir;
	struct s_dirInfos	*next;
}						t_dirInfos;

typedef struct s_heads_list {
	t_dirInfos	*list;
	t_dirInfos	*ret;
	t_dirInfos	*dir_parent;
}				t_heads_list;

typedef struct s_datas {
	t_options	options;
	int			size[SIZE_LENGTH];
}	t_datas;

int				char_is_flag(char c);
void			fill_options(char c, t_options *options);
int				is_untrack_folder(char *str);
int				is_hidden_folder(char *str);
int				max_nbr(int a, int b);

void			free_lst(t_dirInfos **dirList);
void			mem_check(void *pointer, t_dirInfos **dirList);
void			*free_mem_dir(t_dirInfos **list, char **init_path, char **path);

void			set_permision(struct stat dir_stat, char str[SIZE_PERM]);
char			set_file_type(mode_t mode);
void			set_column_size(int size[SIZE_LENGTH], t_dirInfos *dir);

void			print_long_format(t_dirInfos *dir, int size[SIZE_LENGTH]);
void			print_list(t_dirInfos **dirList, t_datas *datas, int isSub);

void			main_struct_init(t_datas *datas);
t_dirInfos		*init_dir_info(char dir_name[256], char *path, int is_sub_dir);
t_subDir_infos	init_sub_dir_infos(int is_sub_dir);
t_heads_list	init_heads_list(t_dirInfos **dirList);

t_dirInfos		*ft_lstadd_first(int size[SIZE_LENGTH], \
	t_heads_list *heads_list, t_dirInfos **new, t_subDir_infos *subDirInfos);
t_dirInfos		*ft_lstadd_second(t_dirInfos **new, t_heads_list *heads_list, \
	t_options	options);

int				parser(char **av, t_options *options);

t_dirInfos		*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList);

int				sort_by_letter(t_dirInfos *new, t_dirInfos *list, int reverse);
int				sort_by_time(t_dirInfos *new, t_dirInfos *list, \
	t_options options);

t_dirInfos		*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList);
t_dirInfos		*browse_dir(t_datas *datas, DIR **p_dir, t_dirInfos **dirList, \
	t_subDir_infos *sub_dir_infos);
int				skip_dir(DIR **p_dir, struct dirent **currt_dir, \
	t_datas *datas);
t_dirInfos		*fill_variable(t_subDir_infos *sub_dir_infos, \
	struct dirent *current_dir, t_dirInfos **dirList, char **str);

#endif