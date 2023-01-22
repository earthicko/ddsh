#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "msgdef.h"

int	builtin_exit(char **argv)
{
	int	stat;
	int	ret;

	if (argv[1] && argv[2])
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", MSG_ERROR_PREFIX);
		return (1);
	}
	if (argv[1])
	{
		ret = ft_atoi_if_valid(argv[1], &stat);
		if (ret)
		{
			ft_dprintf(2, "%s: numeric argument required\n", argv[1]);
			stat = 2;
		}
		exit(stat);
	}
	exit(exit_stat_manager(-1));
}
