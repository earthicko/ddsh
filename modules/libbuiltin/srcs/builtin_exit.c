#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"

int	builtin_exit(char **argv)
{
	int	stat;
	int	ret;

	if (argv[1])
	{
		ret = ft_atoi_if_valid(argv[1], &stat);
		if (ret)
		{
			ft_dprintf(2, "%s: numeric argument required\n", argv[1]);
			stat = 255;
		}
		exit(stat);
	}
	exit(exit_stat_manager(-1));
}
