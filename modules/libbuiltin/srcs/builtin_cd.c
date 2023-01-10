#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "envmanager.h"
#include "builtin_internal.h"

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	if (!ft_strncmp(argv[0], FLAG_OLDPWD, ft_strlen(FLAG_OLDPWD)))
	{
		if (envmanager(NULL, &target, ENVVAR_OLDPWD, NULL))
			return (1);
		stat = chdir(target);
		free(target);
		if (stat)
			return (1);
	}
	else
	{
		stat = chdir(argv[0]);
		if (stat)
			return (1);
	}
	return (0);
}
