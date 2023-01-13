#ifndef BUILD_EXEC_H
# define BUILD_EXEC_H

# include "t_node.h"
# include "t_exec_unit.h"

int		build_exec_unit(t_node *root, t_unit_arr *units);
void	units_destroy(t_unit_arr *units);

#endif
