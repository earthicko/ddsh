#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"

static int	builtin_cd_internal(char *target)
{
	char	*pwd;
	int		stat;

	stat = 0;
	pwd = getcwd(NULL, 0);
	if (pwd)
		stat |= envman_setval("OLDPWD", pwd);
	free(pwd);
	stat |= chdir(target);
	pwd = getcwd(NULL, 0);
	if (pwd)
		stat |= envman_setval("PWD", pwd);
	free(pwd);
	if (stat)
		return (1);
	return (CODE_OK);
}

static int	_builtin_cd_to_oldpwd(void)
{
	int		stat;
	char	*target;

	stat = envman_getval("OLDPWD", &target);
	if (stat)
	{
		if (stat == CODE_ERROR_DATA)
			ft_dprintf(2, "%s: cd: OLDPWD not set\n", MSG_ERROR_PREFIX);
		return (1);
	}
	stat = ft_printf("%s\n", target);
	if (stat < 0)
		return (1);
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}

static int	_builtin_cd_to_home(void)
{
	int		stat;
	char	*target;

	stat = envman_getval("HOME", &target);
	if (stat)
	{
		if (stat == CODE_ERROR_DATA)
			ft_dprintf(2, "%s: cd: HOME not set\n", MSG_ERROR_PREFIX);
		return (1);
	}
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}

static int	_builtin_cd_to_cwd(void)
{
	int		stat;
	char	*target;

	target = getcwd(NULL, 0);
	if (!target)
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (1);
	}
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	argv++;
	if (!*argv)
		return (_builtin_cd_to_home());
	else if (!ft_strncmp(*argv, "-", 2))
		return (_builtin_cd_to_oldpwd());
	else if (ft_strlen(*argv) == 0)
		return (_builtin_cd_to_cwd());
	target = ft_strdup(*argv);
	if (!target)
		return (1);
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}
