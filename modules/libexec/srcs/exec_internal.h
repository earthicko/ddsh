/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "t_node.h"
# include "t_exec_unit.h"

int		get_n_unit(t_node *root);
int		get_n_redir(t_node *node);
t_node	*get_child_node(t_node *cmd_elem, int depth);

int		free_unit_member(t_exec_unit *unit);
int		free_single_unit(t_exec_unit *unit, int i, int j);
int		free_all_unit(t_unit_arr *units, int idx);

#endif
