#include "builtin_commands.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//pwd2에서 실행되게 했는데 pwd로 바꾸어야함
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

//무조건 반복문에서 return되긴 함
//cmd자체가 is_builtin_command로부터 온 인자이기 때문
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

// TODO: 리다이션 수행 후, 입출력을 원래대로 복원해야함
// TODO: backup_stdinout 구현할 것
// 명령어 실행전에 redir부터 먼저 처리할 것
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

	if (process_redir(unit->redir_arr, unit->n_redir) == CODE_ERROR_IO)
		return (CODE_ERROR_IO);
	if (cmd_idx == CODE_ERROR_GENERIC)
	{
		dprintf(2, "Failed to map proper cmd index: builtin command\n");
		return (-42);
	}
	return (exec_builtin[cmd_idx](unit->argv));
}
