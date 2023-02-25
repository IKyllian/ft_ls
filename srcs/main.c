#include "ft_ls.h"

void free_mem_dir(t_dirInfos **list, char **init_path, char **path) {
	if (*init_path)
		free(*init_path);
	*init_path = NULL;
	if (*path)
		free(*path);
	freeLst(list);
}

t_heads_list init_heads_list(t_dirInfos **dirList) {
	t_heads_list	new;

	new.dirParent = NULL;
	new.ret = NULL;
	new.list = *dirList;

	return (new);
}

int getDirStat(char **str, struct stat *statBuffer, t_dirInfos **list, char **init_path) {
	if (stat(*str, statBuffer) < 0) {
		ft_printf("Error while Stat\n");
		free_mem_dir(list, init_path, str);
		return (-1);
	}
	return (0);
}

t_dirInfos *execDir(t_datas *datas, DIR **pDir, t_dirInfos **dirList, t_subDir_infos *subDirInfos)
{
	struct dirent	*currentDir;
	struct stat		statBuffer;
	t_heads_list	heads_list;
	char			*str;

	str = NULL;
	heads_list = init_heads_list(dirList);
	while((currentDir = readdir(*pDir)) != NULL)
	{
		if (!datas->options.showHidden && ishiddenFolder(currentDir->d_name))
			continue;
		str = ft_strjoin(subDirInfos->init_path, currentDir->d_name);
		mem_check(str, dirList);
		if (getDirStat(&str, &statBuffer, &heads_list.list, &subDirInfos->init_path) < 0)
			return (NULL);

		if (subDirInfos->isSubDir && subDirInfos->isFirstDir) {
			if ((heads_list.ret = ft_lstadd(&heads_list.list, statBuffer, currentDir->d_name, str, subDirInfos, datas->options.reverse, &heads_list.dirParent, datas->size)) == NULL) {
				free_mem_dir(&heads_list.list, &subDirInfos->init_path, &str);
				return (NULL);
			}
			heads_list.dirParent = heads_list.list;
			heads_list.list = heads_list.list->subDir;
		} else {
			if ((heads_list.ret = ft_lstadd(&heads_list.list, statBuffer, currentDir->d_name, str, subDirInfos, datas->options.reverse, &heads_list.dirParent, datas->size)) == NULL) {
				free_mem_dir(&heads_list.list, &subDirInfos->init_path, &str);
				return (NULL);
			}
		}

		if (datas->options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			if (readFolder(datas, str, 1, &heads_list.ret) == NULL) {
				free_mem_dir(&heads_list.list, &subDirInfos->init_path, &str);
				return (NULL);
			}
		}
		if (str)
			free(str);
	}
	return (heads_list.list);
}

t_subDir_infos init_subDir_infos(int isSubDir)
{
	t_subDir_infos	new;

	new.init_path = NULL;
	new.isFirstDir = 1;
	new.isSubDir = isSubDir;

	return (new);
}

t_dirInfos *readFolder(t_datas *datas, char *path, int isSubdir, t_dirInfos **dirList)
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

	ret = execDir(datas, &pDir, dirList, &subDirInfos);
	if (subDirInfos.init_path)
		free(subDirInfos.init_path);
	closedir(pDir);
	return (ret);
}

// t_dirInfos *readFolder(t_datas *datas, char *path, int isSubdir, t_dirInfos **dirList)
// {
// 	DIR *pDir;
// 	struct dirent *currentDir;
// 	struct stat statBuffer;
// 	int isFirstDir = 1;
// 	t_dirInfos *list = *dirList;
// 	t_dirInfos *ret;
// 	t_dirInfos *dirParent = NULL;
// 	char *str = NULL;
// 	char *firstStr;

// 	if (path && path[ft_strlen(path) - 1] == '/')
// 		firstStr = ft_strjoin(path, NULL);
// 	else
// 		firstStr = ft_strjoin(path, "/");
// 	mem_check(firstStr, dirList);

// 	pDir = opendir(path);
// 	mem_check(pDir, dirList);

// 	while((currentDir = readdir(pDir)) != NULL) {
// 		if (!datas->options.showHidden && ishiddenFolder(currentDir->d_name))	{
// 			continue;
// 		}
// 		str = ft_strjoin(firstStr, currentDir->d_name);
// 		mem_check(str, dirList);
// 		if (stat(str, &statBuffer) < 0) {
// 			ft_printf("Error while Stat\n");
// 			if (firstStr)
// 				free(firstStr);
// 			if (str)
// 				free(str);
// 			freeLst(&list);
// 			return (NULL);
// 		}
	
// 		if (isSubdir && isFirstDir) {
// 			if ((ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, datas->options.reverse, &dirParent, datas->size)) == NULL) {
// 				freeLst(&list);
// 				return (NULL);
// 			}
// 			dirParent = list;
// 			list = list->subDir;
// 		} else {
// 			if ((ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, datas->options.reverse, &dirParent, datas->size)) == NULL) {
// 				freeLst(&list);
// 				return (NULL);
// 			}
// 		}
// 		if (datas->options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
// 			if (readFolder(datas, str, 1, &ret) == NULL) {
// 				freeLst(&list);
// 				return (NULL);
// 			}
// 		}
// 		if (str)
// 			free(str);
// 	}
// 	if (firstStr)
// 		free(firstStr);
// 	closedir(pDir);
// 	return (list);
// }

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
		dirList = readFolder(&datas, av[pathIndex], 0, &dirList);
	else
		dirList = readFolder(&datas, ".", 0, &dirList);

	if (dirList == NULL)
		return (-1);

	printList(&dirList, &datas, 0);
	freeLst(&dirList);

    return (0);
}