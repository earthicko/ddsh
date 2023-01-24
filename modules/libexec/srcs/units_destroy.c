/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   units_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"

void	units_destroy(t_execunit *units, int n_units)
{
	_free_all_unit(units, n_units);
}
