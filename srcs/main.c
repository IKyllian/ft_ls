#include "ft_ls.h"

t_dirInfos *readFolder(t_datas *datas, char *path, int isSubdir, t_dirInfos **dirList)
{
	DIR *pDir;
	struct dirent *currentDir;
	struct stat statBuffer;
	int isFirstDir = 1;
	t_dirInfos *list = *dirList;
	t_dirInfos *ret;
	t_dirInfos *dirParent = NULL;
	char *str = NULL;
	char *firstStr;

	if (path && path[ft_strlen(path) - 1] == '/')
		firstStr = ft_strjoin(path, NULL);
	else
		firstStr = ft_strjoin(path, "/");
	mem_check(firstStr, dirList);

	pDir = opendir(path);
	mem_check(pDir, dirList);

	while((currentDir = readdir(pDir)) != NULL) {
		if (!datas->options.showHidden && ishiddenFolder(currentDir->d_name))	{
			continue;
		}
		str = ft_strjoin(firstStr, currentDir->d_name);
		mem_check(str, dirList);
		if (stat(str, &statBuffer) < 0) {
			ft_printf("Error while Stat\n");
			if (firstStr)
				free(firstStr);
			if (str)
				free(str);
			freeLst(&list);
			return (NULL);
		}
	
		if (isSubdir && isFirstDir) {
			if ((ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, datas->options.reverse, &dirParent, datas->size)) == NULL) {
				freeLst(&list);
				return (NULL);
			}
			dirParent = list;
			list = list->subDir;
		} else {
			if ((ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, datas->options.reverse, &dirParent, datas->size)) == NULL) {
				freeLst(&list);
				return (NULL);
			}
		}
		if (datas->options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			if (readFolder(datas, str, 1, &ret) == NULL) {
				freeLst(&list);
				return (NULL);
			}
		}
		if (str)
			free(str);
	}
	if (firstStr)
		free(firstStr);
	closedir(pDir);
	return (list);
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

	if (pathIndex > 0)
		dirList = readFolder(&datas, av[pathIndex], 0, &dirList);
	else
		dirList = readFolder(&datas, ".", 0, &dirList);

	printList(&dirList, &datas, 0);
	freeLst(&dirList);

    return (0);
}