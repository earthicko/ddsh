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

int	exec_pipeseq_dup_stdio(t_pipeset *pipeset, int n_units, int idx);
int	exec_pipeseq_fork_abort(pid_t *pids, int n, int send_kill, int stat);
int	exec_pipeset_close_parent_pipe(t_pipeset *pipeset, int n_units, int idx);

static void	exec_pipeseq_init_childproc(
		t_pipeset *pipeset, t_node *pipeseq, int n, int i)
{
	if (signal_set_state_default() || exec_pipeseq_dup_stdio(pipeset, n, i) < 0)
		exit(EXIT_FAILURE);
	exit(exec_simplecom(node_get_nthchild(pipeseq, i)));
}

int	exec_pipeseq_fork(t_node *pipeseq, int n_simplecom)
{
	pid_t		*pids;
	int			i;
	t_pipeset	pipeset;

	pids = malloc(sizeof(pid_t) * n_simplecom);
	if (!pids)
		return (CODE_ERROR_MALLOC);
	i = 0;
	while (i < n_simplecom)
	{
		if (i < n_simplecom - 1 && pipe(pipeset.new_pipe) < 0)
			return (exec_pipeseq_fork_abort(
					pids, n_simplecom, TRUE, CODE_ERROR_IO));
		pids[i] = fork();
		if (pids[i] < 0)
			return (exec_pipeseq_fork_abort(
					pids, n_simplecom, TRUE, CODE_ERROR_GENERIC));
		if (pids[i] == 0)
			exec_pipeseq_init_childproc(&pipeset, pipeseq, n_simplecom, i);
		if (exec_pipeset_close_parent_pipe(&pipeset, n_simplecom, i) < 0)
			return (CODE_ERROR_IO);
		ft_memcpy(pipeset.old_pipe, pipeset.new_pipe, sizeof(pipeset.new_pipe));
		i++;
	}
	return (exec_pipeseq_fork_abort(pids, n_simplecom, TRUE, CODE_OK));
}
