#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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

static char	*append_filenum(char *filename, int n)
{
	char	*numstr;
	char	*appended;

	numstr = ft_itoa(n);
	if (!numstr)
		return (NULL);
	appended = ft_strjoin(filename, numstr);
	free(numstr);
	return (appended);
}

static char	*generate_filename(int n)
{
	int		slot;
	char	*temp1;
	char	*temp2;

	slot = ttyslot();
	if (slot < 0)
		return (NULL);
	temp1 = ttyname(slot);
	if (!temp1)
		return (NULL);
	temp2 = extract_filename(temp1);
	free(temp1);
	if (!temp2)
		return (NULL);
	temp1 = ft_strjoin(PREFIX_HEREDOC_TEMPFILE, temp2);
	free(temp2);
	if (!temp1)
		return (NULL);
	temp2 = append_filenum(temp1, n);
	free(temp1);
	return (temp2);
}

int	heredoc_create(int *n_heredoc)
{
	pid_t	pid;
	char	*filename;

	filename = generate_filename(*n_heredoc);
	ft_printf("filename %s\n", filename);
	pid = fork();
	if (pid == -1)
		return (CODE_ERROR_GENERIC);
	if (pid)
		waitpid(pid, NULL, 0);
	else
		ft_printf("Unimplemented stub of heredoc_create child.\n");
	free(filename);
	(*n_heredoc)++;
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
