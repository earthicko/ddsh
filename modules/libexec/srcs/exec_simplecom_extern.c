/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecom_extern.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:19:20 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/27 16:19:20 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "libft.h"
#include "envmanager.h"
#include "sighandler.h"
#include "msgdef.h"
#include "strutils.h"

static void	_exec_simplecom_prepare_extern(char **argv, char ***envp_buf)
{
	int			_stat;
	struct stat	s_statbuf;

	_stat = find_exec(&argv[0]);
	if (_stat == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (_stat == CODE_ERROR_GENERIC)
		exit(127);
	if (envman_setval("_", argv[0], TRUE) || envman_getenvp(envp_buf)
		|| signal_set_state_default())
		exit(EXIT_FAILURE);
	if (stat(argv[0], &s_statbuf) != 0)
		exit(EXIT_FAILURE);
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s%s: is a directory\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	if (access(argv[0], X_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
}

int	_exec_simplecom_fork_extern(char **argv)
{
	pid_t	pid;
	char	**envp;
	int		_stat;

	pid = fork();
	if (pid < 0)
	{
		ft_dprintf(2, "%sfailed to fork.\n", MSG_ERROR_PREFIX);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		_exec_simplecom_prepare_extern(argv, &envp);
		execve(argv[0], argv, envp);
	}
	waitpid(pid, &_stat, 0);
	if (WIFSIGNALED(_stat))
		return (WTERMSIG(_stat) + 128);
	else
		return (WEXITSTATUS(_stat));
}
