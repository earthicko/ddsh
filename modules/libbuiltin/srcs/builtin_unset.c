#include <stddef.h>
#include "envmanager.h"

int	builtin_unset(char **argv)
{
	while (*argv)
	{
		envmanager(NULL, NULL, *argv, NULL);
		argv++;
	}
	return (0);
}
