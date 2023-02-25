#include "ft_ls.h"

void *free_mem_dir(t_dirInfos **list, char **init_path, char **path) {
	if (*init_path)
		free(*init_path);
	*init_path = NULL;
	if (*path)
		free(*path);
	freeLst(list);
	return (NULL);
}

t_heads_list init_heads_list(t_dirInfos **dirList) {
	t_heads_list	new;

	new.dirParent = NULL;
	new.ret = NULL;
	new.list = *dirList;
	return (new);
}

t_dirInfos *browseDir(t_datas *datas, DIR **pDir, t_dirInfos **dirList, t_subDir_infos *subDirInfos)
{
	struct dirent	*currentDir;
	t_heads_list	heads_list;
	t_dirInfos		*new;
	char			*str;

	str = NULL;
	heads_list = init_heads_list(dirList);
	while((currentDir = readdir(*pDir)) != NULL)
	{
		if (!datas->options.showHidden && ishiddenFolder(currentDir->d_name))
			continue;
		str = ft_strjoin(subDirInfos->init_path, currentDir->d_name);
		mem_check(str, dirList);
		new = init_dirInfo(currentDir->d_name, str, subDirInfos->isSubDir);
		mem_check(new, dirList);
		if ((heads_list.ret = ft_lstadd_first(datas->size, &heads_list, &new, subDirInfos)) == NULL
			&& (heads_list.ret = ft_lstadd_second(&new, &heads_list, datas->options.reverse)) == NULL)
			return (free_mem_dir(&heads_list.list, &subDirInfos->init_path, &str));
		if (datas->options.listSubdir && S_ISDIR(heads_list.ret->dirStat.st_mode) && !isUntrackFolder(currentDir->d_name)
			&& readDir(datas, str, 1, &heads_list.ret) == NULL)
			return (free_mem_dir(&heads_list.list, &subDirInfos->init_path, &str));
		if (str)
			free(str);
	}
	return (heads_list.list);
}

t_dirInfos *readDir(t_datas *datas, char *path, int isSubdir, t_dirInfos **dirList)
{
	DIR				*pDir;
	t_subDir_infos	subDirInfos;
	t_dirInfos		*ret;

	subDirInfos = init_subDir_infos(isSubdir);
	if (path && path[ft_strlen(path) - 1] == '/')
		subDirInfos.init_path = ft_strjoin(path, NULL);
	else
		subDirInfos.init_path = ft_strjoin(path, "/");
	mem_check(subDirInfos.init_path, dirList);

	pDir = opendir(path);
	mem_check(pDir, dirList);

	ret = browseDir(datas, &pDir, dirList, &subDirInfos);
	if (subDirInfos.init_path)
		free(subDirInfos.init_path);
	closedir(pDir);
	return (ret);
}

int main(int ac, char **av)
{	
	int			pathIndex;
	t_dirInfos	*dirList;
	t_datas		datas;

	dirList = NULL;
	pathIndex = -1;
	main_struct_init(&datas);
	if (ac > 1)
		pathIndex = parser(av, &datas.options);

	if (pathIndex == -2)
		return (-1);
	if (pathIndex > 0)
		dirList = readDir(&datas, av[pathIndex], 0, &dirList);
	else
		dirList = readDir(&datas, ".", 0, &dirList);
	if (dirList == NULL)
		return (-1);

	printList(&dirList, &datas, 0);
	freeLst(&dirList);
    return (0);
}