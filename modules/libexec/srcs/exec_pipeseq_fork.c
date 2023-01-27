/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeseq_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:19:10 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/27 16:19:11 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "t_node.h"
#include "sighandler.h"
#include "executor_internal.h"

int	_exec_pipeseq_dup_stdio(int *pipeset, int n_units, int idx);
int	_exec_pipeseq_fork_abort(pid_t *pids, int n, int send_kill);
int	_exec_pipeset_close_parent_pipe(int *pipeset, int n_units, int idx);

static void	_exec_pipeseq_init_childproc(
		int *pipeset, t_node *pipeseq, int n, int i)
{
	if (signal_set_state_default()
		|| _exec_pipeseq_dup_stdio(pipeset, n, i) < 0)
		exit(EXIT_FAILURE);
	exit(_exec_simplecom(node_get_nthchild(pipeseq, i)));
}

int	_exec_pipeseq_fork(t_node *pipeseq, int n_simplecom)
{
	pid_t	*pids;
	int		i;
	int		pipeset[4];

	pids = malloc(sizeof(pid_t) * n_simplecom);
	if (!pids)
		return (CODE_ERROR_MALLOC);
	i = 0;
	while (i < n_simplecom)
	{
		if (i < n_simplecom - 1 && pipe(pipeset) < 0)
			return (_exec_pipeseq_fork_abort(pids, n_simplecom, TRUE));
		pids[i] = fork();
		if (pids[i] < 0)
			return (_exec_pipeseq_fork_abort(pids, n_simplecom, TRUE));
		if (pids[i] == 0)
			_exec_pipeseq_init_childproc(pipeset, pipeseq, n_simplecom, i);
		if (_exec_pipeset_close_parent_pipe(pipeset, n_simplecom, i) < 0)
			return (_exec_pipeseq_fork_abort(pids, n_simplecom, TRUE));
		ft_memcpy(pipeset + 2, pipeset, sizeof(int) * 2);
		i++;
	}
	return (_exec_pipeseq_fork_abort(pids, n_simplecom, FALSE));
}
