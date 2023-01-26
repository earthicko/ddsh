/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H
# include "t_node.h"
# include "./t_execunit/t_execunit.h"

# define WRITE 1
# define READ 0
# define STDINOUT_BACKUP 0
# define STDINOUT_RESTORE 1
# define SUBSHELL 0
# define PARENTSHELL 1

typedef struct s_pipeset
{
	int	next[2];
	int	prev[2];
}	t_pipeset;

t_node	*_get_nth_child(t_node *root, int n);
int		_io_manager(int mode, int *fdbuf);

int		_exec_pipeseq(
			t_exec_pipeseq *exec);
int		_exec_pipeseq_fork(
			t_exec_pipeseq *units);
void	_exec_simplecom_forked(
			t_pipeset *pipeset, t_exec_simplecom *exec, int n_coms, int idx);
int		_exec_simplecom_builtin(
			t_exec_simplecom *unit, int mode);
int		_exec_redirs(t_list *redirs);

#endif
