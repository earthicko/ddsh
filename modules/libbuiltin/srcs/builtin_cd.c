#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"
#include "libft_def.h"

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
	if (stat)
		return (1);
	return (CODE_OK);
}

static int	_exit_builtin_cd(int stat, char *cause)
{
	if (stat == CODE_ERROR_DATA)
		ft_dprintf(2, "%s: cd: %s not set\n", MSG_ERROR_PREFIX, cause);
	if (stat)
		return (1);
	return (0);
}

static int	_builtin_cd_settarget_oldpwd(char **target)
{
	int	stat;

	stat = envman_getval("OLDPWD", target);
	if (stat)
		return (_exit_builtin_cd(stat, "OLDPWD"));
	ft_printf("%s\n", *target);
	return (0);
}

static int	_builtin_cd_settarget_home(char **target)
{
	int	stat;

	stat = envman_getval("HOME", target);
	if (stat)
		return (_exit_builtin_cd(stat, "HOME"));
	return (0);
}

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	argv++;
	if (*argv && !ft_strncmp(*argv, "-", 2))
	{
		if (_builtin_cd_settarget_oldpwd(&target))
			return (1);
	}
	else if ((*argv && ft_strlen(*argv) == 0) || !*argv)
	{
		if (_builtin_cd_settarget_home(&target))
			return (1);
	}
	else
	{
		target = ft_strdup(*argv);
		if (!target)
			return (1);
	}
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}
