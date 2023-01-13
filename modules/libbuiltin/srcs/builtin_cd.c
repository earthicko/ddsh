#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "envmanager.h"
#include "builtin_internal.h"

static int	builtin_cd_internal(char *target)
{
	char	*pwd;
	int		stat;

	pwd = getcwd(NULL, 0);
	if (pwd)
		envmanager(NULL, NULL, ENVVAR_OLDPWD, pwd);
	free(pwd);
	stat = chdir(target);
	pwd = getcwd(NULL, 0);
	if (pwd)
		envmanager(NULL, NULL, ENVVAR_PWD, pwd);
	free(pwd);
	return (stat);
}

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	if (!ft_strncmp(argv[0], FLAG_OLDPWD, ft_strlen(FLAG_OLDPWD)))
	{
		if (envmanager(NULL, &target, ENVVAR_OLDPWD, NULL))
		{
			printf("Unimplemented error message of cd.\n");
			return (1);
		}
	}
	else
	{
		target = ft_strdup(argv[0]);
		if (!target)
			return (1);
	}
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}
