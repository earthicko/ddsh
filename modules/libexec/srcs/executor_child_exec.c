#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "envmanager.h"
#include "executor_internal.h"
#include "sighandler.h"
#include "msgdef.h"
#include "libft.h"
#include "strutils.h"

static int	set_fd_stream(t_info *info)
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];

	if (info->units->n_unit == 1)
		return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (info->cur_idx == info->n_unit - 1)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
}

void	if_dir_then_exit_126(char *cmd_name)
{
	struct stat	s_statbuf;

	if (stat(cmd_name, &s_statbuf) != 0)
	{
		ft_dprintf(2, "%s: %s: failed to fetch stat\n",
			MSG_ERROR_PREFIX, cmd_name);
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s: %s: is a directory\n", MSG_ERROR_PREFIX, cmd_name);
		exit(126);
	}
}

void	child_exec_extern(t_info *info)
{
	char	**argv;
	int		status;
	char	**envp_paths;

	argv = (info->units->arr + info->cur_idx)->argv;
	status = envman_getenvp(&envp_paths);
	if (status)
		exit(EXIT_FAILURE);
	status = find_exec(&argv[0]);
	if (status == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (status == CODE_ERROR_GENERIC)
		exit(127);
	if_dir_then_exit_126(argv[0]);	
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp_paths);
	else 
	{
		ft_dprintf(2, "%s: %s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	exit(127);
}

// TODO: 빌트인 커맨드 실패에 대한 exit status 세분화
 void	child_exec_cmd(t_info *info)
{
	char	**argv;
	int		builtin_stat;

	if (signal_set_state_default() || set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	argv = (info->units->arr + info->cur_idx)->argv;
	if (is_builtin_command(argv[0]) != FALSE)
	{
		// TODO: 빌트인함수 에러메시지 출력은 서브루틴에 추가
		// CODE_OK가 아닌 상황에서 exit status 세분화 필요
		builtin_stat = exec_builtin_cmd(info->units->arr + info->cur_idx, SUBSHELL);
		if (builtin_stat != CODE_OK)
			exit(EXIT_FAILURE);
		exit(CODE_OK);
	}
	child_exec_extern(info);
}
