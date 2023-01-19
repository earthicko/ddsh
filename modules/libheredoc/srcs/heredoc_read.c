#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "strutils.h"
#include "libft.h"
#include "envmanager.h"
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

static int	_should_expand(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (FALSE);
		str++;
	}
	return (TRUE);
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
	delim_dup = ft_strdup(delimeter);
	if (!delim_dup)
		exit(1);
	expand = _should_expand(delim_dup);
	if (remove_quotes(&delim_dup))
		_abort_write_to_file(fd, filename, delim_dup, 1);
	while (TRUE)
	{
		stat = _write_io_file_loop(fd, expand, delim_dup);
		if (stat < 0)
			_abort_write_to_file(fd, filename, delim_dup, 1);
		if (stat > 0)
			break ;
	}
	_abort_write_to_file(fd, filename, delim_dup, 0);
}

int	_heredoc_read(int *n_heredoc, char *prefix_filename, char *delimeter)
{
	pid_t	pid;
	char	*filename;
	int		stat;

	(*n_heredoc)++;
	stat = _heredoc_get_filename(
			*n_heredoc, prefix_filename, (*n_heredoc) - 1, &filename);
	(*n_heredoc)--;
	if (stat)
		return (stat);
	pid = fork();
	if (pid == -1)
		return (CODE_ERROR_GENERIC);
	stat = CODE_OK;
	if (pid)
		wait4(pid, &stat, 0, NULL);
	else
		_write_to_file(filename, delimeter);
	free(filename);
	stat = WEXITSTATUS(stat);
	if (!stat)
		(*n_heredoc)++;
	return (stat);
}
