#include "ft_ls.h"

int	dup_owner(t_dirInfos **new, struct passwd *owner_infos)
{
	(*new)->owner = ft_strdup(owner_infos->pw_name);
	if (!(*new)->owner)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		if ((*new)->path)
			free((*new)->path);
		return (-1);
	}
	return (0);
}

int dup_gr_name(t_dirInfos **new, struct group *group_infos)
{
	(*new)->gr_name = ft_strdup(group_infos->gr_name);
	if (!(*new)->gr_name)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		if ((*new)->path)
			free((*new)->path);
		if ((*new)->owner)
			free((*new)->owner);
		return (-1);
	}
	return (0);
}

int	dup_strings(t_dirInfos **new, char dir_name[256], struct stat dir_stat, \
	char *path)
{
	struct group	*group_infos;
	struct passwd	*owner_infos;
	int				ret;

	group_infos = getgrgid(dir_stat.st_gid);
	owner_infos = getpwuid(dir_stat.st_uid);
	if (!group_infos || !owner_infos)
		return (-1);
	(*new)->dir_name = ft_strdup(dir_name);
	if (!(*new)->dir_name)
		return (-1);
	(*new)->path = ft_strdup(path);
	if (!(*new)->path)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		return (-1);
	}
	ret = dup_owner(new, owner_infos);
	if (ret < 0)
		return (ret);
	ret = dup_gr_name(new, group_infos);
	if (ret < 0)
		return (ret);
	return (0);
}
