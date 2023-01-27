#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"
#include "sighandler.h"
#include "t_node.h"
#include "executor_internal.h"

#include <stdio.h>

void	exec_pipeseq_destroy_pipes(int *pipes, int n_pipes);
int		exec_pipeseq_create_pipes(int **pipes, int n_pipes);

static void	exec_pipeseq_wait_pids(pid_t *pids, int n, int send_kill)
{
	int	i;
	int	exit_stat;

	if (send_kill)
	{
		i = 0;
		while (i < n)
		{
			kill(pids[i], SIGKILL);
			i++;
		}
	}
	i = 0;
	while (i < n)
	{
		wait4(pids[i], &exit_stat, 0, NULL);
		if (i == n - 1)
		{
			if (WIFSIGNALED(exit_stat))
				exit_stat_manager(WTERMSIG(exit_stat) + 128);
			else
				exit_stat_manager(WEXITSTATUS(exit_stat));
		}
		i++;
	}
}

static int	exec_pipeseq_redir_stdinout(int *pipes, int n, int i)
{
	int	stat;

	ft_dprintf(2, "%s: pid %d: n %d i %d\n", __func__, getpid(), n, i);
	stat = 0;
	if (i != 0)
	{
		if (dup2(pipes[(i - 1) * 2 + READ], STDIN_FILENO) < 0)
			stat = CODE_ERROR_IO;
	}
	if (i != n - 1)
	{
		if (dup2(pipes[(i - 0) * 2 + WRITE], STDOUT_FILENO) < 0)
			stat = CODE_ERROR_IO;
	}
	return (stat);
}

static void	exec_pipeseq_init_childproc(
		int *pipes, t_node *pipeseq, int n, int i)
{
	ft_dprintf(2, "%s: pid %d\n", __func__, getpid());

	if (signal_set_state_default() || exec_pipeseq_redir_stdinout(pipes, n, i))
	{
		ft_dprintf(2, "%s: pid %d: exit(EXIT_FAILURE)\n", __func__, getpid());
		exit(EXIT_FAILURE);
	}
	exec_pipeseq_destroy_pipes(pipes, n - 1);
	exit(exec_simplecom(node_get_nthchild(pipeseq, i)));
}

static int	exec_pipeseq_fork(int *pipes, t_node *pipeseq, int n_simplecom)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * n_simplecom);
	if (!pids)
		return (CODE_ERROR_MALLOC);
	ft_bzero(pids, sizeof(pid_t) * n_simplecom);
	i = 0;
	while (i < n_simplecom)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			exec_pipeseq_wait_pids(pids, i, TRUE);
			free(pids);
			return (CODE_ERROR_GENERIC);
		}
		if (pids[i] == 0)
			exec_pipeseq_init_childproc(pipes, pipeseq, n_simplecom, i);
		i++;
	}
	exec_pipeseq_wait_pids(pids, n_simplecom, FALSE);
	free(pids);
	return (CODE_OK);
}

int	exec_pipeseq_usepipe(t_node *pipeseq, int n_simplecom)
{
	int	stat;
	int	*pipes;

	stat = exec_pipeseq_create_pipes(&pipes, n_simplecom - 1);
	if (stat)
		return (stat);
	stat = exec_pipeseq_fork(pipes, pipeseq, n_simplecom);
	exec_pipeseq_destroy_pipes(pipes, n_simplecom - 1);
	return (stat);
}
