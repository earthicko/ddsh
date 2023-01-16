#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "strutils.h"
#include "heredoc_internal.h"

static char	*extract_filename(int slot)
{
	char	*cursor;
	char	*fullname;

	fullname = ttyname(slot);
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

static int	setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

static char	*merge_filename(int slot, char *temp_dir, int doc_id)
{
	char	*strs[2];
	char	*result;

	strs[0] = extract_filename(slot);
	if (!strs[0])
		return (NULL);
	strs[1] = ft_itoa(doc_id);
	if (!strs[1])
	{
		free(strs[0]);
		return (NULL);
	}
	if (temp_dir)
		result = ft_strmerge(5,
				temp_dir, PREFIX_HEREDOC_TEMPFILE, strs[0], "_", strs[1]);
	else
		result = ft_strmerge(4,
				PREFIX_HEREDOC_TEMPFILE, strs[0], "_", strs[1]);
	free(strs[0]);
	free(strs[1]);
	return (result);
}

int	heredoc_get_filename(int n_heredoc, char *temp_dir, int doc_id, char **buf)
{
	int		slot;
	char	*result;

	if (doc_id < 0 || n_heredoc <= doc_id)
		return (setval_and_return(buf, NULL, CODE_ERROR_SCOPE));
	slot = ttyslot();
	if (slot < 0)
		return (setval_and_return(buf, NULL, CODE_ERROR_GENERIC));
	result = merge_filename(slot, temp_dir, doc_id);
	if (!result)
		return (setval_and_return(buf, NULL, CODE_ERROR_GENERIC));
	return (setval_and_return(buf, result, CODE_OK));
}

int	heredoc_get_nextfilename(
		int n_heredoc, char *temp_dir, int *i_current, char **buf)
{
	int	stat;

	stat = heredoc_get_filename(n_heredoc, temp_dir, *i_current, buf);
	if (!stat)
		(*i_current)++;
	return (stat);
}
