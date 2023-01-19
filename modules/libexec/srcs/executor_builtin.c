#include "builtin_commands.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


static int	map_cmd(char *cmd)
{

	const char	*builtin_cmds[8] = {
		"",
		"cd",
		"echo",
		"export",
		"pwd",
		"unset",
		"env",
		"exit"
	};
	const int	cmd_len = ft_strlen(cmd);
	int			i;

	i = -1;
	while (++i < 8)
		if (ft_strncmp(builtin_cmds[i], cmd, cmd_len + 1) == 0)
			return (i);
	return (CODE_ERROR_GENERIC);
}

// TODO: cmd_idx 매핑 오류(절대 발생하지 않을 경우)의 오류 방어 처리가 필요한지
// 마지막에 최종 검토 마치고 삭제하는 것으로
int	exec_builtin_cmd(t_exec_unit *unit, int mode)
{
	const t_exec_builtin	exec_builtin[8] = {
		0, builtin_cd, builtin_echo,  builtin_export,
		builtin_pwd, builtin_unset, builtin_env, builtin_exit
	};
	const int				cmd_idx = map_cmd(unit->argv[0]);
	int						stat;

	if (mode == PARENTSHELL)
		io_manager(STDINOUT_BACKUP);
	stat = process_redir(unit->redir_arr, unit->n_redir);
	if (stat == CODE_ERROR_IO)
		return (1);

	// CODE TO BE REMOVED: 삭제해도 되는 분기
	if (cmd_idx == CODE_ERROR_GENERIC)
	{
		dprintf(2, "%s, Failed to map proper cmd index\n", __func__);
		return (-42);
	}
	stat = exec_builtin[cmd_idx](unit->argv);
	if (mode == PARENTSHELL)
		io_manager(STDINOUT_RESTORE);
	return (stat);
}
