#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <stdlib.h>
# include "t_exec_unit.h"
# include "t_node.h"

int		get_n_unit(t_node *root);
int		get_n_redir(t_node *node);
t_node	*get_child_node(t_node *cmd_elem, int depth);

int		free_unit_member(t_exec_unit *unit);
int		free_single_unit(t_exec_unit *unit, int i, int j);
int		free_all_unit(t_unit_arr *units, int idx);

#endif
