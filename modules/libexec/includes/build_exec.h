/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_EXEC_H
# define BUILD_EXEC_H

# include "t_node.h"
# include "t_execunit.h"

int		build_exec_unit(t_node *root, t_execunit **units, int *n_units);

#endif
