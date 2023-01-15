#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "strutils.h"
#include "executor_internal.h"

static int	wait_children(pid_t last_cmd, int n_unit)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = EXIT_FAILURE;
	i = -1;
	while (++i < n_unit)
		if (last_cmd == wait(&status))
			exit_status = WEXITSTATUS(status);
	return (exit_status);
}

static int	parent_close_unused_pipe(t_info *info)
{
	int	stat;

	stat = CODE_OK;
	if (info->cur_idx == 0)
		stat = close(info->new_pipe[WRITE]);
	else if (info->cur_idx == info->n_unit - 1)
		stat = close(info->old_pipe[READ]);
	else
		if (close(info->old_pipe[READ]) < 0 || close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (stat);
}

static void	init_info(t_info *info, t_unit_arr *units)
{
	info->units = units;
	info->n_unit = units->n_unit;
	info->cur_idx = 0;
}

//구조체를 그냥 하나 만들까..?
//변수 각각 선언하고 매개변수로 넘길바에 나은 거 같기도 하고..
//
//마지막 커맨드의 pid를 어디다가 저장하지? ㅇㅁㅇ
//전역변수..?
static int	fork_exec(t_unit_arr *units)
{
	t_info	info;
	pid_t	pid;

	init_info(&info, units);
	while (info.cur_idx < info.n_unit)
	{
		if (info.cur_idx < info.n_unit - 1)
			if (pipe(info.new_pipe) < 0)
				return (CODE_ERROR_IO);
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
			child_exec_cmd(&info);
		if (parent_close_unused_pipe(&info) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(info.old_pipe, info.new_pipe, sizeof(info.new_pipe));
	}
	return (wait_children(pid, info.n_unit));
}

//executor의 리턴값을 $?에 저장하기
int	executor(t_unit_arr *units)
{
	//n_unit이 0이하인 경우는 없을듯?
	if (units->n_unit <= 0)
		return (CODE_ERROR_SCOPE);
	if (units->n_unit == 1)
		if (is_builtin_command(units->arr->argv[0]))
			return (exec_builtin_cmd(units->arr));
	return (fork_exec(units));
}
