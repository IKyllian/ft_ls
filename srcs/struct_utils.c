#include "ft_ls.h"

void	main_struct_init(t_datas *datas)
{
	datas->options.longFormat = 0;
	datas->options.reverse = 0;
	datas->options.showHidden = 0;
	datas->options.listSubdir = 0;
	datas->options.sortTime = 0;
	ft_bzero(datas->size, sizeof(datas->size));
}

int dup_strings(t_dirInfos **new, char dirName[256], struct stat dirStat, char *path)
{
	struct group	*groupInfos;
	struct passwd	*ownerInfos;

	groupInfos = getgrgid(dirStat.st_gid);
	if (!groupInfos)
        return (-1);
	ownerInfos = getpwuid(dirStat.st_uid);
	(*new)->dirName = ft_strdup(dirName);
	if (!(*new)->dirName)
		return (-1);
	(*new)->path = ft_strdup(path);
	if (!(*new)->path)
		return (-1);
	(*new)->owner = ft_strdup(ownerInfos->pw_name);
	if (!(*new)->owner)
		return (-1);
	(*new)->gr_name = ft_strdup(groupInfos->gr_name);
	if (!(*new)->gr_name)
		return (-1);
	return (0);
}

t_dirInfos	*init_dirInfo(char dirName[256], char *path, int isSubdir)
{
	t_dirInfos	*new;
	struct stat	statBuffer;

	if (stat(path, &statBuffer) < 0)
	{
		ft_printf("Error while Stat\n");
		return (NULL);
	}
	new = (t_dirInfos *)malloc(sizeof(t_dirInfos));
	if (!new)
		return (NULL);
	if (dup_strings(&new, dirName, statBuffer, path) < 0)
		return (NULL);
	new->dirStat = statBuffer;
	new->isSubdir = isSubdir;
	new->subDir = NULL;
	new->next = NULL;
	new->blocksSize = 0;
	return (new);
}

t_subDir_infos init_subDir_infos(int isSubDir)
{
	t_subDir_infos	new;

	new.init_path = NULL;
	new.isFirstDir = 1;
	new.isSubDir = isSubDir;
	return (new);
}