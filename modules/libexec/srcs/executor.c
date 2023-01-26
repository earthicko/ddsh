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

#include "libft.h"
#include "msgdef.h"
#include "./t_execunit/t_execunit.h"
#include "executor_internal.h"

int	execute_tree(t_node *parse_tree)
{
	int				stat;
	t_exec_pipeseq	*exec;

	exec = exec_pipeseq_create(parse_tree);
	if (!exec)
	{
		ft_dprintf(2, "%scritical: failed to build exec unit\n",
			MSG_ERROR_PREFIX);
		return (CODE_ERROR_GENERIC);
	}
	stat = _exec_pipeseq(exec);
	exec_pipeseq_destroy(exec);
	return (stat);
}
