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

static int	_set_fd(
		t_pipeset *pipeset, t_exec_simplecom *exec, int n_units, int idx)
{
	if (n_units == 1)
		return (_exec_redirs(exec->redirs));
	if (idx == 0)
	{
		if (close(pipeset->next[READ]) < 0
			|| dup2(pipeset->next[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->next[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (idx == n_units - 1)
	{
		if (dup2(pipeset->prev[READ], STDIN_FILENO) < 0
			|| close(pipeset->prev[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(pipeset->next[READ]) < 0
			|| dup2(pipeset->prev[READ], STDIN_FILENO) < 0
			|| close(pipeset->prev[READ]) < 0
			|| dup2(pipeset->next[WRITE], STDOUT_FILENO) < 0
			|| close(pipeset->next[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (_exec_redirs(exec->redirs));
}

void	_if_dir_exit(char *cmd_name)
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

void	_exec_extern(char	**argv)
{
	int		_stat;
	char	**envp_paths;

	if (!argv[0])
		exit(EXIT_SUCCESS);
	_stat = find_exec(&argv[0]);
	if (_stat == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (_stat == CODE_ERROR_GENERIC)
		exit(127);
	if (envman_setval("_", argv[0], TRUE) || envman_getenvp(&envp_paths))
		exit(EXIT_FAILURE);
	_if_dir_exit(argv[0]);
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp_paths);
	else
	{
		ft_dprintf(2, "%s%s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	exit(127);
}

void	_exec_simplecom_forked(
		t_pipeset *pipeset, t_exec_simplecom *exec, int n_coms, int idx)
{
	char		**argv;

	if (exec_simplecom_getargv(exec, &argv))
		exit(EXIT_FAILURE);
	if (signal_set_state_default() || _set_fd(pipeset, exec, n_coms, idx) < 0)
		exit(EXIT_FAILURE);
	if (argv[0] && builtin_getindex(argv[0]) >= 0)
		exit(_exec_simplecom_builtin(exec, SUBSHELL));
	else
		_exec_extern(argv);
}
