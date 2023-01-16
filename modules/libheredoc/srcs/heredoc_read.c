#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "strutils.h"
#include "libft.h"
#include "envmanager.h"
#include "heredoc_internal.h"

static int	write_io_file_loop(int fd, int expand, char *delimeter)
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
		if (envman_replace_envvar(&line, FALSE))
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

static int	should_expand(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	abort_write_to_file(int fd, char *filename, char *delim, int stat)
{
	close(fd);
	free(delim);
	unlink(filename);
	exit(stat);
}

static void	write_to_file(char *filename, char *delimeter)
{
	int		fd;
	int		stat;
	int		expand;
	char	*delim_dup;

	unlink(filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		exit(1);
	delim_dup = ft_strdup(delimeter);
	if (!delim_dup)
		exit(1);
	expand = should_expand(delim_dup);
	if (remove_quotes(&delim_dup))
		abort_write_to_file(fd, filename, delim_dup, 1);
	while (TRUE)
	{
		stat = write_io_file_loop(fd, expand, delim_dup);
		if (stat < 0)
			abort_write_to_file(fd, filename, delim_dup, 1);
		if (stat > 0)
			break ;
	}
	abort_write_to_file(fd, filename, delim_dup, 0);
}

int	heredoc_read_(int *n_heredoc, char *temp_dir, char *delimeter)
{
	pid_t	pid;
	char	*filename;
	int		stat;

	(*n_heredoc)++;
	stat = heredoc_get_filename_(
			*n_heredoc, temp_dir, (*n_heredoc) - 1, &filename);
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
		write_to_file(filename, delimeter);
	free(filename);
	if (!stat)
		(*n_heredoc)++;
	return (stat);
}
