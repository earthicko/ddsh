/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:53 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "strutils.h"
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"
#include "expansion.h"
#include "heredoc_internal.h"
#include "sighandler.h"

void	rl_clear_history(void);

static int	_write_io_file_loop(int fd, int expand, char *delimeter)
{
	int		stat;
	char	*line;

	line = readline(PREFIX_HEREDOC_PROMPT);
	if (!line)
		return (1);
	if (!ft_strncmp(line, delimeter, ft_strlen(delimeter) + 1))
	{
		free(line);
		return (1);
	}
	if (expand)
	{
		if (do_heredoc_expansion(&line))
		{
			free(line);
			return (-1);
		}
	}
	stat = ft_dprintf(fd, "%s\n", line);
	free(line);
	if (stat < 0)
		return (-1);
	return (0);
}

static int	_handle_delimeter_expansion(char *delim, char **delim2, int *expand)
{
	*delim2 = ft_strdup(delim);
	if (!(*delim2))
		exit(1);
	*expand = TRUE;
	while (*delim)
	{
		if (*delim == '\'' || *delim == '\"')
			*expand = FALSE;
		delim++;
	}
	return (remove_quotes(delim2));
}

static void	_abort_write_to_file(int fd, char *filename, char *delim, int stat)
{
	close(fd);
	free(delim);
	if (stat)
		unlink(filename);
	exit(stat);
}

static void	_write_to_file(char *filename, char *delimeter)
{
	int		fd;
	int		stat;
	int		expand;
	char	*delim_dup;

	rl_clear_history();
	stat = signal_set_state_heredoc();
	if (stat)
		exit(1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		exit(1);
	if (_handle_delimeter_expansion(delimeter, &delim_dup, &expand))
		_abort_write_to_file(fd, filename, delim_dup, 1);
	while (access(filename, R_OK) == 0)
	{
		stat = _write_io_file_loop(fd, expand, delim_dup);
		if (stat < 0)
			_abort_write_to_file(fd, filename, delim_dup, 1);
		if (stat > 0)
			_abort_write_to_file(fd, filename, delim_dup, 0);
	}
	_abort_write_to_file(fd, filename, delim_dup, 1);
}

int	_heredoc_read(char *ttyname, int *n_heredoc, char *delimeter)
{
	pid_t	pid;
	char	*filename;
	int		stat;

	(*n_heredoc)++;
	stat = _heredoc_get_filename(
			ttyname, *n_heredoc, (*n_heredoc) - 1, &filename);
	(*n_heredoc)--;
	if (stat)
		return (stat);
	pid = fork();
	if (pid == -1)
		return (CODE_ERROR_GENERIC);
	stat = CODE_OK;
	if (pid)
		waitpid(pid, &stat, 0);
	else
		_write_to_file(filename, delimeter);
	free(filename);
	stat = WEXITSTATUS(stat);
	if (stat == 0 || stat >= 128)
		(*n_heredoc)++;
	else
		ft_dprintf(2, "%scannot write to here-document.\n", MSG_ERROR_PREFIX);
	return (stat);
}
