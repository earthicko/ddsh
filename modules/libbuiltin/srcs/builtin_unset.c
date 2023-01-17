#include "envmanager.h"

int	builtin_unset(char **argv)
{
	argv++;
	while (*argv)
	{
		envman_unsetval(*argv);
		argv++;
	}
	return (0);
}
