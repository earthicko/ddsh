#include <stddef.h>
#include "envmanager.h"

int	builtin_unset(char **argv)
{
	while (*argv)
	{
		// envmanager에 unset 기능 구현해야 동작함
		if (envmanager(NULL, NULL, *argv, NULL))
			return (1);
		argv++;
	}
	return (0);
}
