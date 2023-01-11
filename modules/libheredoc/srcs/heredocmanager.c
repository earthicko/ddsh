#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "heredoc_internal.h"

int	heredoc_write(int *n_heredoc, int doc_id)
{
	char	*filename;
	int		fd;

	if (doc_id < 0 || doc_id >= *n_heredoc)
		return (CODE_ERROR_SCOPE);
	filename = generate_filename(doc_id);
	if (!filename)
		return (CODE_ERROR_GENERIC);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	if (fd < 0 || dup2(fd, STDIN_FILENO) != fd)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

static int	heredoc_clear_entry(int n)
{
	char	*filename;

	filename = generate_filename(n);
	if (!filename)
		return (CODE_ERROR_GENERIC);
	unlink(filename);
	free(filename);
	return (CODE_OK);
}

int	heredoc_clear(int *n_heredoc, int n)
{
	int		i;

	if (n < 0)
	{
		i = 0;
		while (i < *n_heredoc)
		{
			if (heredoc_clear_entry(i))
				return (CODE_ERROR_GENERIC);
			i++;
		}
	}
	else if (0 <= n && n < *n_heredoc)
	{
		if (heredoc_clear_entry(n))
			return (CODE_ERROR_GENERIC);
		*n_heredoc = 0;
	}
	return (CODE_OK);
}

int	heredocmanager(int mode, int doc_id, char *delimeter)
{
	static int	n_heredoc;

	if (mode == HEREDOCMODE_CREATE)
		return (heredoc_read(&n_heredoc, doc_id, delimeter));
	if (mode == HEREDOCMODE_GETFD)
		return (heredoc_write(&n_heredoc, doc_id));
	if (mode == HEREDOCMODE_CLEAR)
		return (heredoc_clear(&n_heredoc, doc_id));
	return (CODE_ERROR_SCOPE);
}
