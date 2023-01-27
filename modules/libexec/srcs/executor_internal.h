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

# define WRITE 1
# define READ 0
# define STDINOUT_BACKUP 0
# define STDINOUT_RESTORE 1

typedef struct s_pipeset
{
	int	new_pipe[2];
	int	old_pipe[2];
}	t_pipeset;

int		_io_manager(int mode, int *fdbuf);

int		exec_pipeseq(t_node *pipeseq);
int		exec_simplecom(t_node *simplecom);
int		exec_io_redir(t_node *io_redir);

#endif
