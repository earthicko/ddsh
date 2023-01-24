/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/23 13:31:28 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "builtin_commands.h"
#include "envmanager.h"
#include "sighandler.h"
#include "strutils.h"
#include "msgdef.h"
#include "executor_internal.h"

static int	_set_fd_stream(
		t_pipeset *pipeset, t_execunit *units, int n_units, int idx)
{
	const t_execunit	cur_unit = units[idx];

	if (n_units == 1)
		return (_process_redir(cur_unit.redir_arr, cur_unit.n_redir));
	if (idx == 0)
	{
		if (close(pipeset->new_pipe[READ]) < 0
			|| dup2(pipeset->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (idx == n_units - 1)
	{
		if (dup2(pipeset->old_pipe[READ], STDIN_FILENO) < 0
			|| close(pipeset->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(pipeset->new_pipe[READ]) < 0
			|| dup2(pipeset->old_pipe[READ], STDIN_FILENO) < 0
			|| close(pipeset->old_pipe[READ]) < 0
			|| dup2(pipeset->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (_process_redir(cur_unit.redir_arr, cur_unit.n_redir));
}

void	_if_dir_then_exit_126(char *cmd_name)
{
	struct stat	s_statbuf;

	if (stat(cmd_name, &s_statbuf) != 0)
	{
		ft_dprintf(2, "%s%s: failed to fetch stat\n",
			MSG_ERROR_PREFIX, cmd_name);
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s%s: is a directory\n", MSG_ERROR_PREFIX, cmd_name);
		exit(126);
	}
}

void	_child_exec_extern(t_execunit *units, int idx)
{
	char	**argv;
	int		status;
	char	**envp_paths;

	argv = (units[idx]).argv;
	if (!argv[0])
		exit(EXIT_SUCCESS);
	status = find_exec(&argv[0]);
	if (status == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (status == CODE_ERROR_GENERIC)
		exit(127);
	if (envman_setval("_", argv[0]) || envman_getenvp(&envp_paths))
		exit(EXIT_FAILURE);
	_if_dir_then_exit_126(argv[0]);
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp_paths);
	else
	{
		ft_dprintf(2, "%s%s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	exit(127);
}

void	_child_exec_cmd(
		t_pipeset *pipeset, t_execunit *units, int n_units, int idx)
{
	t_execunit	*unit_ptr;
	char		**argv;

	unit_ptr = units + idx;
	argv = unit_ptr->argv;
	if (signal_set_state_default()
		|| _set_fd_stream(pipeset, units, n_units, idx) < 0)
		exit(EXIT_FAILURE);
	if (argv[0] && builtin_getindex(argv[0]) >= 0)
		exit(_exec_builtin_cmd(units + idx, SUBSHELL));
	else
		_child_exec_extern(units, idx);
}
