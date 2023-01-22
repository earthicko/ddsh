/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_build_fail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "exec_internal.h"
#include "libft_def.h"
#include "t_exec_unit.h"

int	free_unit_member(t_exec_unit *unit)
{
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

int	free_single_unit(t_exec_unit *unit, int i, int j)
{
	int	idx;

	idx = -1;
	while (++idx < i)
		free(unit->argv[idx]);
	idx = -1;
	while (++idx < j)
		free(unit->redir_arr[idx].content);
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

int	free_all_unit(t_unit_arr *units, int idx)
{
	int	i;

	i = -1;
	if (!units->arr)
		return (CODE_OK);
	while (++i < idx)
		free_single_unit(units->arr + i, units->arr[i].n_word, \
				units->arr[i].n_redir);
	free(units->arr);
	units->arr = 0;
	return (CODE_ERROR_MALLOC);
}
