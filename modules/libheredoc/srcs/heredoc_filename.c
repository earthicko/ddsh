#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "strutils.h"
#include "heredoc_internal.h"

static int	_setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

static char	*_merge_filename(char *prefix_filename, int doc_id)
{
	char	*docidstr;
	char	*result;

	docidstr = ft_itoa(doc_id);
	if (!docidstr)
		return (NULL);
	result = ft_strjoin(prefix_filename, docidstr);
	free(docidstr);
	return (result);
}

int	_heredoc_get_filename(int n_heredoc, char *prefix_filename, int doc_id, char **buf)
{
	char	*result;

	if (doc_id < 0 || n_heredoc <= doc_id)
		return (_setval_and_return(buf, NULL, CODE_ERROR_SCOPE));
	result = _merge_filename(prefix_filename, doc_id);
	if (!result)
		return (_setval_and_return(buf, NULL, CODE_ERROR_GENERIC));
	return (_setval_and_return(buf, result, CODE_OK));
}

int	_heredoc_get_next_filename(
		int n_heredoc, char *temp_dir, int *i_current, char **buf)
{
	int	stat;

	stat = _heredoc_get_filename(n_heredoc, temp_dir, *i_current, buf);
	if (!stat)
		(*i_current)++;
	return (stat);
}
