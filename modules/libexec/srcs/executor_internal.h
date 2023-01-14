#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include <unistd.h>
# include "t_exec_unit.h"

typedef struct s_info
{
	t_unit_arr *units;
	int			n_unit;
	int			cur_idx;
	int			new_pipe[2];
	int			old_pipe[2];
}	t_info;

typedef int	(*t_do_redir)(t_redir *redir_arr);

int	do_redir_in(t_redir *redir_arr);
int	do_redir_out(t_redir *redir_arr);
int	do_redir_in_here(t_redir *redir_arr);
int	do_redir_out_append(t_redir *redir_arr);

void	child_exec_cmd(t_info *info);

# define WRITE 1
# define READ 0

#endif
