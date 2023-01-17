#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "envmanager.h"

static int	builtin_cd_internal(char *target)
{
	char	*pwd;
	int		stat;

	pwd = getcwd(NULL, 0);
	if (pwd)
		envman_setval("OLDPWD", pwd);
	free(pwd);
	stat = chdir(target);
	pwd = getcwd(NULL, 0);
	if (pwd)
		envman_setval("PWD", pwd);
	free(pwd);
	return (stat);
}

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	argv++;
	if (*argv && !ft_strncmp(*argv, "-", 2))
	{
		if (envman_getval("OLDPWD", &target))
		{
			printf("Unimplemented error message of cd.\n");
			return (1);
		}
		printf("%s\n", target);
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
