#include "ft_ls.h"

int	charIsFlag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	return (0);
}

int	arrayLength(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	fillOptions(char c, t_options *options)
{
	if (c == 'r')
		options->reverse = 1;
	else if (c == 'a')
		options->showHidden = 1;
	else if (c == 'l')
		options->longFormat = 1;
	else if (c == 'R')
		options->listSubdir = 1;
}

int	isUntrackFolder(char *str)
{
	if (ft_strlen(str) == 1 && str[0] == '.')
		return (1);
	else if (ft_strlen(str) == 2 && str[0] == '.' && str[1] == '.')
		return (1);
	return (0);
}

int	ishiddenFolder(char *str)
{
	if (ft_strlen(str) > 0 && str[0] == '.')
		return (1);
	return (0);
}