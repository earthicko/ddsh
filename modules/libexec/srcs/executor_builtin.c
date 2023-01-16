#include "builtin_commands.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int	builtin_pwd2(char **argv)
{
	char	*pwd;
	int		stat;

	(void)argv;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	stat = printf("%s\n", pwd);
	free(pwd);
	if (stat < 0)
		return (1);
	return (0);
}

//무조건 반복문에서 걸리긴 함
//cmd자체가 is_builtin_command에서 추출된 애임
static int	map_cmd(char *cmd)
{
	const char	*builtin_cmds[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};
	const int	cmd_len = ft_strlen(cmd);
	int			i;

	i = -1;
	while (++i < 7)
		if (ft_strncmp(builtin_cmds[i], cmd, cmd_len + 1) == 0)
			return (i);
	return (CODE_ERROR_GENERIC);
}

int	exec_builtin_cmd(t_exec_unit *unit)
{
	const t_exec_builtin	exec_builtin[7] = {
		builtin_echo,
		builtin_cd,
		builtin_pwd2,
		builtin_export,
		builtin_unset,
		builtin_env,
		builtin_exit
	};
	const int				cmd_idx = map_cmd(unit->argv[0]);

	//이렇게하면 개망함, 표준 입출력 리다이렉션을 어디다가 반드시 저장해놔야함
	//backup_stdinout();
	//순서는 리다이렉션 먼저 무조건!
	if (process_redir(unit->redir_arr, unit->n_redir) == CODE_ERROR_IO)
		return (CODE_ERROR_IO);
	//리턴값 고칠 것
	if (cmd_idx == CODE_ERROR_GENERIC)
	{
		dprintf(2, "Failed to map proper cmd index: builtin command\n");
		return (-42);
	}
	return (exec_builtin[cmd_idx](unit->argv));
}
