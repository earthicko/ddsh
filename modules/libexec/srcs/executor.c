#include "libft.h"
#include "executor_internal.h"


#include "strutils.h"

static int	parent_close_unused_pipe(t_info *info)
{
	int	stat;

	if (info->cur_idx == 0)
		stat = close(info->new_pipe[WRITE]);
	else if (info->cur_idx == info->n_unit - 1)
		stat = close(info->old_pipe[READ]);
	else
	{
		if (close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
		stat = close(info->new_pipe[WRITE]);
	}
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
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
			child_exec_cmd(&info);
		if (parent_close_unused_pipe(&info) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(info.old_pipe, info.new_pipe, sizeof(info.new_pipe));
	}
	return (CODE_OK);
}

int	executor(t_unit_arr *units)
{
	//n_unit이 0이하인 경우는 없을듯?
	if (units->n_unit <= 0)
		return (CODE_ERROR_SCOPE);
	if (units->n_unit == 1)
		if (is_builtin_command(units->arr[0].argv[0]))
			return (exec_builtin_command(units));
	return (fork_exec(units));
}
