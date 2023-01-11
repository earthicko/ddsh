#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "libft.h"
#include "heredoc_internal.h"

static char	*extract_filename(char *fullname)
{
	char	*cursor;

	cursor = fullname;
	while (*cursor)
		cursor++;
	while (cursor != fullname)
	{
		if (*cursor == '/')
			break ;
		cursor--;
	}
	if (*cursor == '/')
		cursor++;
	return (ft_strdup(cursor));
}

static char	*generate_filename(void)
{
	int		slot;
	char	*fullname;
	char	*filename;

	slot = ttyslot();
	if (slot < 0)
		return (NULL);
	fullname = ttyname(slot);
	if (!fullname)
		return (NULL);
	filename = extract_filename(fullname);
	if (!filename)
		return (NULL);
	return (ft_strjoin(PREFIX_HEREDOC_TEMPFILE, filename));
}

int	heredoc_create(int *n_heredoc)
{
	char	*filename;

	(void)n_heredoc;
	filename = generate_filename();
	ft_printf("filename %s\n", filename);
	free(filename);
	return (ft_printf("Unimplemented stub of heredoc_create.\n"));
}

int	heredoc_getfd(int *n_heredoc, int n)
{
	(void)n_heredoc;
	(void)n;
	return (ft_printf("Unimplemented stub of heredoc_create.\n"));
}

int	heredoc_clear(int *n_heredoc, int n)
{
	(void)n_heredoc;
	(void)n;
	return (ft_printf("Unimplemented stub of heredoc_create.\n"));
}

int	heredocmanager(int mode, int n)
{
	static int	n_heredoc;

	if (mode == HEREDOCMODE_CREATE)
		return (heredoc_create(&n_heredoc));
	if (mode == HEREDOCMODE_GETFD)
		return (heredoc_getfd(&n_heredoc, n));
	if (mode == HEREDOCMODE_CLEAR)
		return (heredoc_clear(&n_heredoc, n));
	return (CODE_ERROR_SCOPE);
}
