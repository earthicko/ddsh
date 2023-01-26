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

int	_exec_simplecom_builtin(t_exec_simplecom *exec, int mode)
{
	int		stat;
	int		fdbuf[2];
	char	**argv;

	if (exec_simplecom_getargv(exec, &argv))
		return (1);
	if (mode == PARENTSHELL && _io_manager(STDINOUT_BACKUP, fdbuf))
	{
		ft_free_strarr(argv);
		return (1);
	}
	stat = _exec_redirs(exec->redirs);
	if (stat == CODE_ERROR_IO)
	{
		ft_free_strarr(argv);
		return (1);
	}
	stat = builtin_exec_by_name(argv[0], argv);
	ft_free_strarr(argv);
	if (mode == PARENTSHELL && _io_manager(STDINOUT_RESTORE, fdbuf))
		return (1);
	return (stat);
}
