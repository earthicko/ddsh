#include <errno.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "libft_def.h"
#include "strutils.h"
#include "executor_internal.h"


#include <sys/errno.h>

static int	wait_children(pid_t last_cmd, int n_unit)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = EXIT_FAILURE;
	i = -1;
	while (++i < n_unit)
	{
		if (last_cmd == wait(&status))
		{
			//dprintf(2, "here, children?\n");
			exit_status = WEXITSTATUS(status);
		}
	}
	dprintf(2, "in %s, exit_status: %d\n", __func__, exit_status);
	return (exit_status);
}

static int	parent_close_unused_pipe(t_info *info)
{
	int	stat;

	stat = CODE_OK;
	if (info->units->n_unit == 1)
		return (CODE_OK);
	if (info->cur_idx == 0)
		stat = close(info->new_pipe[WRITE]);
	else if (info->cur_idx == info->n_unit - 1)
		stat = close(info->old_pipe[READ]);
	else
		if (close(info->old_pipe[READ]) < 0 || close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
//	dprintf(2, "in %s, errno: %d\n", __func__, errno);
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
//		dprintf(2, "in %s, before fork errno: %d\n", __func__, errno);
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
		{
//			dprintf(2, "in %s, child errno: %d\n", __func__, errno);
			child_exec_cmd(&info);
		}
		if (parent_close_unused_pipe(&info) < 0)
		{
//			dprintf(2, "failed to parent close\n");
			return (CODE_ERROR_IO);
		}
//		dprintf(2, "in %s, parents errno: %d\n", __func__, errno);
		ft_memcpy(info.old_pipe, info.new_pipe, sizeof(info.new_pipe));
		info.cur_idx++;
	}
	return (wait_children(pid, info.n_unit));
}

//executor의 리턴값을 $?에 저장하기
int	executor(t_unit_arr *units)
{
	//printf("in %s\n", __func__);
	//n_unit이 0이하인 경우는 없을듯?
	if (units->n_unit <= 0)
		return (CODE_ERROR_SCOPE);
	if (units->n_unit == 1)
		if (is_builtin_command(units->arr->argv[0]) && dprintf(2, "before exec_builtin_cmd\n"))
			return (exec_builtin_cmd(units->arr));
	//printf("in %s, before fork_exec\n", __func__);
	return (fork_exec(units));
}
