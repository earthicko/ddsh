#include "libft.h"
#include "envmanager.h"
#include "msgdef.h"
#include "strutils.h"

int	builtin_unset(char **argv)
{
	argv++;
	while (*argv)
	{
		if (is_valid_name(*argv))
			envman_unsetval(*argv);
		else
			ft_dprintf(2, "%s: unset: `%s': not a valid identifier\n",
				MSG_ERROR_PREFIX, *argv);
		argv++;
	}
	return (0);
}
