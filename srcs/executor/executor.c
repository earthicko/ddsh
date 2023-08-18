/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envmanager.h"
#include "executor_internal.h"

int	execute_tree(t_node *parse_tree)
{
	int	stat;

	stat = _exec_pipeseq(parse_tree);
	exit_stat_manager(stat);
	return (CODE_OK);
}
