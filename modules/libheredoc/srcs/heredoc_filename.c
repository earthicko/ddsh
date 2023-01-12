#include <stdlib.h>
#include <unistd.h>
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

static char	*append_filenum(char *filename, int doc_id)
{
	char	*numstr;
	char	*appended;

	numstr = ft_itoa(doc_id);
	if (!numstr)
		return (NULL);
	appended = ft_strjoin(filename, numstr);
	free(numstr);
	return (appended);
}

static int	setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

int	heredoc_get_filename(int n_heredoc, int doc_id, char **buf)
{
	int		slot;
	char	*temp1;
	char	*temp2;

	if (doc_id < 0 || n_heredoc <= doc_id)
		return (setval_and_return(buf, NULL, CODE_ERROR_SCOPE));
	slot = ttyslot();
	if (slot < 0)
		return (setval_and_return(buf, NULL, CODE_ERROR_GENERIC));
	temp1 = ttyname(slot);
	if (!temp1)
		return (setval_and_return(buf, NULL, CODE_ERROR_GENERIC));
	temp2 = extract_filename(temp1);
	if (!temp2)
		return (setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	temp1 = ft_strjoin(PREFIX_HEREDOC_TEMPFILE, temp2);
	free(temp2);
	if (!temp1)
		return (setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	temp2 = append_filenum(temp1, doc_id);
	free(temp1);
	if (!temp2)
		return (setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	return (setval_and_return(buf, temp2, CODE_OK));
}
