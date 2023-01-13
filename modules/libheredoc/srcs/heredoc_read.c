#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "libft.h"
#include "heredoc_internal.h"

static int	write_io_file_loop(int fd, int expand, char *delimeter)
{
	int		stat;
	char	*line;

	line = readline(PREFIX_HEREDOC_PROMPT);
	if (!line)
		return (1);
	if (!ft_strncmp(line, delimeter, ft_strlen(delimeter)))
		return (1);
	if (expand)
		printf("%s: Should expand %s\n", __func__, line);
	stat = ft_dprintf(fd, "%s\n", line);
	if (stat < 0)
		return (-1);
	return (0);
}

static void	write_to_file(char *filename, int expand, char *delimeter)
{
	int	fd;
	int	stat;

	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		exit(1);
	while (TRUE)
	{
		stat = write_io_file_loop(fd, expand, delimeter);
		if (stat < 0)
		{
			close(fd);
			unlink(filename);
			exit(1);
		}
		if (stat > 0)
			break ;
	}
	close(fd);
	exit(0);
}

int	heredoc_read(int *n_heredoc, int expand, char *delimeter)
{
	pid_t	pid;
	char	*filename;
	int		stat;

	(*n_heredoc)++;
	stat = heredoc_get_filename(*n_heredoc, (*n_heredoc) - 1, &filename);
	if (stat)
		return (stat);
	pid = fork();
	if (pid == -1)
		return (CODE_ERROR_GENERIC);
	stat = CODE_OK;
	if (pid)
		wait4(pid, &stat, 0, NULL);
	else
		write_to_file(filename, expand, delimeter);
	free(filename);
	if (stat)
		(*n_heredoc)--;
	return (stat);
}
