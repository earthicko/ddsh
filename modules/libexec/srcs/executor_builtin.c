/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_commands.h"
#include "executor_internal.h"

int	_exec_builtin_cmd(t_execunit *unit, int mode)
{
	int	stat;
	int	fdbuf[2];

	if (mode == PARENTSHELL && _io_manager(STDINOUT_BACKUP, fdbuf))
		return (1);
	stat = _process_redir(unit->redir_arr, unit->n_redir);
	if (stat == CODE_ERROR_IO)
		return (1);
	stat = builtin_exec_by_name(unit->argv[0], unit->argv);
	if (mode == PARENTSHELL && _io_manager(STDINOUT_RESTORE, fdbuf))
		return (1);
	return (stat);
}
