/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:19:07 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/27 16:19:09 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envmanager.h"
#include "t_node.h"
#include "executor_internal.h"

int	exec_pipeseq_fork(t_node *pipeseq, int n_simplecom);

int	exec_pipeseq(t_node *pipeseq)
{
	int	n_simplecom;
	int	fdbuf[2];

	n_simplecom = ft_lstsize(pipeseq->childs);
	if (n_simplecom > 1)
		return (exec_pipeseq_fork(pipeseq, n_simplecom));
	else if (n_simplecom == 1)
	{
		if (_io_manager(STDINOUT_BACKUP, fdbuf))
			return (CODE_ERROR_IO);
		exit_stat_manager(exec_simplecom(node_get_nthchild(pipeseq, 0)));
		if (_io_manager(STDINOUT_RESTORE, fdbuf))
			return (CODE_ERROR_IO);
		return (CODE_OK);
	}
	return (CODE_OK);
}
