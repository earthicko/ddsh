#include <stddef.h>
#include "envmanager.h"

int	builtin_unset(char **argv)
{
	while (*argv)
	{
		envman_unsetval(*argv);
		argv++;
	}
	return (0);
}
