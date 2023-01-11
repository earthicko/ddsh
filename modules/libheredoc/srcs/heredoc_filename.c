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

char	*generate_filename(int doc_id)
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
	temp2 = append_filenum(temp1, doc_id);
	free(temp1);
	return (temp2);
}
