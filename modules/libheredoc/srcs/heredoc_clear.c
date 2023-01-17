#include <stdlib.h>
#include <unistd.h>
#include "libft_def.h"
#include "heredoc_internal.h"

static int	_heredoc_clear_entry(int n_heredoc, char *prefix_filename, int doc_id)
{
	int		stat;
	char	*filename;

	stat = _heredoc_get_filename(n_heredoc, prefix_filename, doc_id, &filename);
	if (stat)
		return (stat);
	unlink(filename);
	free(filename);
	return (CODE_OK);
}

int	_heredoc_clear(int *n_heredoc, int *i_current, char *prefix_filename, int doc_id)
{
	int	i;

	if (doc_id < 0)
	{
		// TODO: 이렇게 하지 말고 디렉토리 검색해서
		i = 0;
		while (i < *n_heredoc)
		{
			_heredoc_clear_entry(*n_heredoc, prefix_filename, i);
			i++;
		}
		*n_heredoc = 0;
		*i_current = 0;
	}
	else if (0 <= doc_id && doc_id < *n_heredoc)
	{
		if (_heredoc_clear_entry(*n_heredoc, prefix_filename, doc_id))
			return (CODE_ERROR_GENERIC);
	}
	else
		return (CODE_ERROR_SCOPE);
	return (CODE_OK);
}
