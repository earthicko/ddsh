#include "exec_internal.h"

void	units_destroy(t_unit_arr *units)
{
	free_all_unit(units, units->n_unit);
}
