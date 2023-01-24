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
#include "executor_internal.h"
#include "libft.h"
#include "t_execunit.h"

int	_free_unit_member(t_execunit *unit)
{
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

int	_free_single_unit(t_execunit *unit)
{
	int	i;

	ft_free_strarr(unit->argv);
	i = 0;
	while (i < unit->n_redir)
	{
		if (unit->redir_arr[i].content)
			free(unit->redir_arr[i].content);
		i++;
	}
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

int	_free_all_unit(t_execunit *units, int n_units)
{
	int	i;

	if (!units)
		return (CODE_OK);
	i = 0;
	while (i < n_units)
	{
		_free_single_unit(units + i);
		i++;
	}
	free(units);
	return (CODE_ERROR_MALLOC);
}
