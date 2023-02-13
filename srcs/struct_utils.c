#include "ft_ls.h"

void main_struct_init(t_datas *datas) {
	datas->options.longFormat = 0;
	datas->options.reverse = 0;
	datas->options.showHidden = 0;
	datas->options.listSubdir = 0;
	ft_bzero(datas->size, sizeof(datas->size));
}

t_dirInfos *init_dirInfo(struct stat dirStat, char dirName[256], char *path, int isSubdir) {
	t_dirInfos *new;
    struct group *groupInfos;
	struct passwd *ownerInfos;

	groupInfos = getgrgid(dirStat.st_gid);
	if (!groupInfos)
        return (NULL);
	ownerInfos = getpwuid(dirStat.st_uid);

	new = (t_dirInfos *)malloc(sizeof(t_dirInfos));
	if (!new)
		return (NULL);
	new->dirName = ft_strdup(dirName);
	if (!new->dirName)
		return (NULL);
	new->path = ft_strdup(path);
	if (!new->path)
		return (NULL);
	new->owner = ft_strdup(ownerInfos->pw_name);
	if (!new->owner)
		return (NULL);
	new->gr_name = ft_strdup(groupInfos->gr_name);
	if (!new->gr_name)
		return (NULL);
	new->dirStat = dirStat;
	new->isSubdir = isSubdir;
	new->subDir = NULL;
	new->next = NULL;
	new->blocksSize = 0;
	return (new);
}

t_dirInfos *ft_lstadd(t_dirInfos **dirList, struct stat dirStat, char dirName[256], char *path, int isSubdir, int *isFirstDir, int isReverse, t_dirInfos **dirParent, int size[SIZE_LENGTH]) {
	t_dirInfos *list = *dirList;
	t_dirInfos *last  = NULL;
	t_dirInfos *new  = NULL;

	new = init_dirInfo(dirStat, dirName, path, isSubdir);
	if (!new)
		return (NULL);

	setColumnSize(size, new);

	if (*dirList == NULL) {
		new->blocksSize += dirStat.st_blocks;
		*dirList = new;
		*isFirstDir = 0;
		return (*dirList);
	 } else if (*isFirstDir) {
		new->blocksSize += dirStat.st_blocks;
		list->subDir = new;
		*isFirstDir = 0;
		return (new);
	}
	while (list) {
		if ((!isReverse && strcmp(dirName, list->dirName) < 0) || (isReverse && strcmp(dirName, list->dirName) > 0)) {
			new->next = list;
			if (last != NULL)
				last->next = new;
			else {
				new->blocksSize = list->blocksSize;
				new->blocksSize += new->dirStat.st_blocks;
				if (*dirParent)
					(*dirParent)->subDir = new;
				*dirList = new;
				return (new);
			}
			(*dirList)->blocksSize += new->dirStat.st_blocks;
			return (new);
		}
		last = list;
		list = list->next;
	}
	last->next = new;
	(*dirList)->blocksSize += new->dirStat.st_blocks;
	return (new);
}