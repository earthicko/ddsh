#include <unistd.h>
#include "libft.h"

static void	init_is_builtin_command(char **parr)
{
	parr[0] = "cd";
	parr[1] = "echo";
	parr[2] = "export";
	parr[3] = "pwd";
	parr[4] = "unset";
	parr[5] = "env";
	parr[6] = "exit";
}

int	is_builtin_command(char *str)
{
	char	*dict[7];
	int		i;

	init_is_builtin_command(dict);
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(str, dict[i], ft_strlen(dict[i]) + 1) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
