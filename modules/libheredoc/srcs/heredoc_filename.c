#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "strutils.h"
#include "heredoc_internal.h"

static char	*_extract_ttyslotname(void)
{
	char	*cursor;
	char	*fullname;

	fullname = ttyname(ttyslot());
	if (!fullname)
		return (NULL);
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

static int	_setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

int	_heredoc_get_filename(int n_heredoc, int doc_id, char **buf)
{
	char	*_ttyname;
	char	*docname;
	char	*result;

	if (doc_id < 0 || n_heredoc <= doc_id)
		return (_setval_and_return(buf, NULL, CODE_ERROR_SCOPE));
	_ttyname = _extract_ttyslotname();
	if (!_ttyname)
		return (_setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	docname = ft_itoa(doc_id);
	if (!docname)
	{
		free(_ttyname);
		return (_setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	}
	result = ft_strmerge(6, DIR_HEREDOC, "/", PREFIX_HEREDOC_TEMPFILE,
			_ttyname, "_", docname);
	free(_ttyname);
	free(docname);
	if (!result)
		return (_setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	return (_setval_and_return(buf, result, CODE_OK));
}

int	_heredoc_get_next_filename(int n_heredoc, int *i_current, char **buf)
{
	int	stat;

	stat = _heredoc_get_filename(n_heredoc, *i_current, buf);
	if (!stat)
		(*i_current)++;
	return (stat);
}
