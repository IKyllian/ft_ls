#include "ft_ls.h"

int flag_check(char c, t_options *options)
{
    if (!charIsFlag(c))
    {
        ft_printf("ft_ls : invalid option -- %c\n", c);
        ft_printf("usage: ls [-Ralrt] [file ...] \n");
        return (-1);
    }
    fillOptions(c, options);
    return (0);
}

int parser(char **av, t_options *options)
{
	int	i;
	int	j;
	int	isFlag;

	i = 1;
	while (av[i])
	{
        isFlag = 0;
        j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '-')
				isFlag = 1;
			else if (isFlag)
			{
                if (flag_check(av[i][j], options) < 0)
                    return (-2);
			} else
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}