#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "libft.h"
#include "strutils.h"
#include "msgdef.h"
#include "envmanager.h"

int	builtin_export(char **argv);

static void	_builtin_env_print(void)
{
	char	**envp;
	char	**cursor;

	if (envman_getenvp(&envp))
		exit(1);
	cursor = envp;
	while (*cursor)
	{
		if (ft_printf("%s\n", *cursor) < 0)
		{
			ft_free_strarr(envp);
			exit(1);
		}
		cursor++;
	}
	ft_free_strarr(envp);
	exit(0);
}

static void	_if_dir_then_exit_126(char *cmd_name)
{
	struct stat	s_statbuf;

	if (stat(cmd_name, &s_statbuf) != 0)
	{
		ft_dprintf(2, "%s: env: %s: failed to fetch stat\n",
			MSG_ERROR_PREFIX, cmd_name);
		exit(1);
	}
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s: env: %s: is a directory\n",
			MSG_ERROR_PREFIX, cmd_name);
		exit(126);
	}
}

static void	_builtin_env_exec(char **argv)
{
	char	**envp;

	if (envman_getenvp(&envp))
		exit(1);
	_if_dir_then_exit_126(argv[0]);
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp);
	else
	{
		ft_dprintf(2, "%s: env: %s: Permission denied\n",
			MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	exit(127);
}

static void	_builtin_env_child(char **argv)
{
	char	*argv_to_export[3];
	int		stat;

	argv_to_export[0] = "export";
	argv_to_export[2] = NULL;
	while (*argv)
	{
		if (!ft_strchr(*argv, '='))
			break ;
		argv_to_export[1] = *argv;
		builtin_export(argv_to_export);
		argv++;
	}
	if (*argv == NULL)
		_builtin_env_print();
	stat = find_exec(&argv[0]);
	if (stat && stat == CODE_ERROR_GENERIC)
		exit(127);
	if (stat)
		exit(1);
	_builtin_env_exec(argv);
	exit(127);
}

int	builtin_env(char **argv)
{
	pid_t	pid;
	int		stat;

	argv++;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid)
		wait4(pid, &stat, 0, NULL);
	else
		_builtin_env_child(argv);
	return (WEXITSTATUS(stat));
}
