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

# include "t_exec_unit.h"

# define WRITE 1
# define READ 0
# define STDINOUT_BACKUP 0
# define STDINOUT_RESTORE 1
# define SUBSHELL 0
# define PARENTSHELL 1

typedef struct s_info
{
	t_unit_arr	*units;
	int			n_unit;
	int			cur_idx;
	int			new_pipe[2];
	int			old_pipe[2];
}	t_info;

typedef int	(*t_do_redir)(t_redir *redir_arr);
typedef int	(*t_exec_builtin)(char **argv);

int		process_redir(t_redir *redir_arr, int n_redir);
int		do_redir_in(t_redir *redir_arr);
int		do_redir_out(t_redir *redir_arr);
int		do_redir_in_here(t_redir *redir_arr);
int		do_redir_out_append(t_redir *redir_arr);

void	io_manager(int mode);

void	child_exec_cmd(t_info *info);

int		exec_builtin_cmd(t_exec_unit *unit, int mode);

#endif
