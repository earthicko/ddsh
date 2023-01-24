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
# include "t_execunit.h"

# define WRITE 1
# define READ 0
# define STDINOUT_BACKUP 0
# define STDINOUT_RESTORE 1
# define SUBSHELL 0
# define PARENTSHELL 1

typedef struct s_pipeset
{
	int	new_pipe[2];
	int	old_pipe[2];
}	t_pipeset;

int		_get_n_unit(t_node *root);
int		_get_n_redir(t_node *node);
t_node	*_get_child_node(t_node *cmd_elem, int depth);

int		_process_redir(t_redir *redir_arr, int n_redir);
int		_do_redir_in(t_redir *redir_arr);
int		_do_redir_out(t_redir *redir_arr);
int		_do_redir_in_here(t_redir *redir_arr);
int		_do_redir_out_append(t_redir *redir_arr);

int		_io_manager(int mode, int *fdbuf);

void	_child_exec_cmd(
			t_pipeset *pipeset, t_execunit *units, int n_units, int idx);
int		_build_exec_unit(
			t_node *root, t_execunit **units, int *n_units);
int		_exec_builtin_cmd(
			t_execunit *unit, int mode);

#endif
