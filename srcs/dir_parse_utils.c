#include "ft_ls.h"

char	*join_path(char *path)
{
	if (path && path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, NULL));
	else
		return (ft_strjoin(path, "/"));
}

t_dirInfos	*create_file(char **init_path, char *path)
{
	if (*init_path)
		free(*init_path);
	return (init_for_file(path));
}

int	skip_dir(DIR **p_dir, struct dirent **currt_dir, t_datas *datas)
{
	if (!datas->options.show_hidden && is_hidden_folder((*currt_dir)->d_name))
	{
		(*currt_dir) = readdir(*p_dir);
		return (1);
	}
	return (0);
}

void	loop_end(char **str, struct dirent **currt_dir, DIR **p_dir)
{
	if (*str)
		free(*str);
	*currt_dir = readdir(*p_dir);
}