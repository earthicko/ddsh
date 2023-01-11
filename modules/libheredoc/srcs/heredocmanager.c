#include <unistd.h>
#include "libft.h"
#include "heredoc_internal.h"

int	heredoc_create(int *n_heredoc)
{
	(void)n_heredoc;
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
