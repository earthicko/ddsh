/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "strutils.h"
#include "executor_internal.h"

static int	wait_children(pid_t last_cmd, int n_unit)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 1;
	i = -1;
	while (++i < n_unit)
	{
		if (last_cmd == wait(&status))
		{
			if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 128;
			else
				exit_status = WEXITSTATUS(status);
		}
	}
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
	return (stat);
}

static void	init_info(t_info *info, t_unit_arr *units)
{
	info->units = units;
	info->n_unit = units->n_unit;
	info->cur_idx = 0;
}

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
		info.cur_idx++;
	}
	return (wait_children(pid, info.n_unit));
}

int	executor(t_unit_arr *units)
{
	int	stat;

	if (units->n_unit <= 0)
		return (CODE_ERROR_SCOPE);
	if (units->arr->n_word == 0)
	{
		if (io_manager(STDINOUT_BACKUP))
			return (1);
		stat = process_redir(units->arr->redir_arr, units->arr->n_redir);
		if (io_manager(STDINOUT_RESTORE))
			return (1);
		if (stat == CODE_ERROR_IO)
			return (1);
		return (CODE_OK);
	}
	if (units->n_unit == 1
		&& is_builtin_command(units->arr->argv[0]))
		return (exec_builtin_cmd(units->arr, PARENTSHELL));
	return (fork_exec(units));
}
