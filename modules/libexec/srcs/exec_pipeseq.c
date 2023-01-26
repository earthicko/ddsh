/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:18 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:20 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "t_node.h"
#include "builtin_commands.h"
#include "executor_internal.h"
#include "./t_execunit/t_execunit.h"

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

static int	_close_unused_pipe(t_pipeset *pipeset, int n_units, int idx)
{
	int	stat;

	stat = CODE_OK;
	if (n_units == 1)
		return (CODE_OK);
	if (idx == 0)
		stat = close(pipeset->next[WRITE]);
	else if (idx == n_units - 1)
		stat = close(pipeset->prev[READ]);
	else
		if (close(pipeset->prev[READ]) < 0 || close(pipeset->next[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (stat);
}

int	_exec_pipeseq_fork(t_exec_pipeseq *units)
{
	t_pipeset	state;
	pid_t		pid;
	int			n_coms;
	int			idx;

	n_coms = ft_lstsize(units->simplecoms);
	idx = 0;
	while (idx < n_coms)
	{
		if (idx < n_coms - 1 && pipe(state.next) < 0)
			return (CODE_ERROR_IO);
		pid = fork();
		if (pid < 0)
			return (CODE_ERROR_GENERIC);
		if (pid == 0)
			_exec_simplecom_forked(
				&state, get_nth_simplecom(units, idx), n_coms, idx);
		if (_close_unused_pipe(&state, n_coms, idx) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(state.prev, state.next, sizeof(state.next));
		idx++;
	}
	return (_wait_children(pid, n_coms));
}

int	_exec_pipeseq(t_exec_pipeseq *exec)
{
	int					stat;
	int					fdbuf[2];
	int					n_coms;
	t_exec_simplecom	*firstcom;

	firstcom = get_nth_simplecom(exec, 0);
	n_coms = ft_lstsize(exec->simplecoms);
	if (n_coms == 1 && ft_lstsize(firstcom->args) == 0)
	{
		if (_io_manager(STDINOUT_BACKUP, fdbuf))
			return (1);
		stat = _exec_redirs(firstcom->redirs);
		if (_io_manager(STDINOUT_RESTORE, fdbuf))
			return (1);
		if (stat == CODE_ERROR_IO)
			return (1);
		return (CODE_OK);
	}
	if (n_coms == 1 && builtin_getindex(get_nth_arg(firstcom, 0)->content) >= 0)
		return (_exec_simplecom_builtin(firstcom, PARENTSHELL));
	return (_exec_pipeseq_fork(exec));
}
