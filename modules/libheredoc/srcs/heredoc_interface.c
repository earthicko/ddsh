#include "heredoc_internal.h"
#include "libft.h"
#include "msgdef.h"

int	heredoc_read(char *delimeter)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_READ, 0, delimeter);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_get_filename(int doc_id, char **buf)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_GETFILENAME, doc_id, buf);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_get_next_filename(char **buf)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_GETNEXTFILENAME, 0, buf);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_clear(int doc_id)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_CLEAR, doc_id, 0);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
