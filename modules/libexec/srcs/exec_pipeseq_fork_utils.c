/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeseq_fork_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:19:12 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/27 16:19:13 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "libft_def.h"
#include "envmanager.h"
#include "executor_internal.h"

static void	exec_pipeseq_kill_pids(pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

static int	exec_pipeseq_wait_pids(pid_t *pids, int n, int send_kill)
{
	int	i;
	int	exit_stat;

	if (send_kill)
		exec_pipeseq_kill_pids(pids, n);
	i = 0;
	while (i < n)
	{
		wait4(pids[i], &exit_stat, 0, NULL);
		if (i == n - 1)
		{
			if (WIFSIGNALED(exit_stat))
				exit_stat = WTERMSIG(exit_stat) + 128;
			else
				exit_stat = WEXITSTATUS(exit_stat);
		}
		i++;
	}
	if (send_kill)
		return (EXIT_FAILURE);
	return (exit_stat);
}

int	exec_pipeseq_fork_abort(pid_t *pids, int n, int send_kill)
{
	int	stat;

	stat = exec_pipeseq_wait_pids(pids, n, send_kill);
	free(pids);
	return (stat);
}

int	exec_pipeset_close_parent_pipe(t_pipeset *pipeset, int n_units, int idx)
{
	int	stat;

	stat = CODE_OK;
	if (n_units == 1)
		return (CODE_OK);
	if (idx == 0)
		stat = close(pipeset->new_pipe[WRITE]);
	else if (idx == n_units - 1)
		stat = close(pipeset->old_pipe[READ]);
	else
		if (close(pipeset->old_pipe[READ]) < 0
			|| close(pipeset->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (stat);
}

int	exec_pipeseq_dup_stdio(t_pipeset *pipeset, int n_units, int idx)
{
	if (n_units == 1)
		return (CODE_OK);
	if (idx == 0)
	{
		if (close(pipeset->new_pipe[READ]) < 0
			|| dup2(pipeset->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (idx == n_units - 1)
	{
		if (dup2(pipeset->old_pipe[READ], STDIN_FILENO) < 0
			|| close(pipeset->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(pipeset->new_pipe[READ]) < 0
			|| dup2(pipeset->old_pipe[READ], STDIN_FILENO) < 0
			|| close(pipeset->old_pipe[READ]) < 0
			|| dup2(pipeset->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (CODE_OK);
}
