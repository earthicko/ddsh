#include "builtin_commands.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"

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
	while (++i)
		if (ft_strncmp(builtin_cmds[0], cmd, cmd_len + 1) == 0)
			return (i);
	//세그 폴트 내려고 -1 하는게 나을듯
	return (-1);
}

//builtin_pwd 함수 매개변수형 맞추면 좋을듯
int	exec_builtin_cmd(t_exec_unit *unit)
{
	const t_exec_builtin	exec_builtin[7] = {
		builtin_echo,
		builtin_cd,
		builtin_pwd,
		builtin_export,
		builtin_unset,
		builtin_env,
		builtin_exit
	};

	if (process_redir(unit->redir_arr, unit->n_redir) == CODE_ERROR_IO)
		return (CODE_ERROR_IO);
	return (exec_builtin[map_cmd(unit->argv[0])](unit->argv));
}
