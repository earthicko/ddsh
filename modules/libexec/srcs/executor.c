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

static int	_wait_children(pid_t last_cmd, int n_units)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 1;
	i = 0;
	while (i < n_units)
	{
		if (last_cmd == wait(&status))
		{
			if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 128;
			else
				exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_status);
}

static int	_parent_close_unused_pipe(t_execstate *info, int n_units)
{
	int	stat;

	stat = CODE_OK;
	if (n_units == 1)
		return (CODE_OK);
	if (info->cur_idx == 0)
		stat = close(info->new_pipe[WRITE]);
	else if (info->cur_idx == n_units - 1)
		stat = close(info->old_pipe[READ]);
	else
		if (close(info->old_pipe[READ]) < 0 || close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (stat);
}

static int	_fork_exec(t_execunit *units, int n_units)
{
	t_execstate	info;
	pid_t		pid;

	info.cur_idx = 0;
	while (info.cur_idx < n_units)
	{
		if (info.cur_idx < n_units - 1)
			if (pipe(info.new_pipe) < 0)
				return (CODE_ERROR_IO);
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
			_child_exec_cmd(&info, units, n_units);
		if (_parent_close_unused_pipe(&info, n_units) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(info.old_pipe, info.new_pipe, sizeof(info.new_pipe));
		info.cur_idx++;
	}
	return (_wait_children(pid, n_units));
}

int	executor(t_execunit *units, int n_units)
{
	int	stat;

	if (units->n_word == 0)
	{
		if (_io_manager(STDINOUT_BACKUP))
			return (1);
		stat = _process_redir(units->redir_arr, units->n_redir);
		if (_io_manager(STDINOUT_RESTORE))
			return (1);
		if (stat == CODE_ERROR_IO)
			return (1);
		return (CODE_OK);
	}
	if (n_units == 1 && is_builtin_command(units->argv[0]))
		return (_exec_builtin_cmd(units, PARENTSHELL));
	return (_fork_exec(units, n_units));
}
