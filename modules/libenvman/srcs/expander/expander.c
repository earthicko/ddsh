#include <stdlib.h>
#include "libft_def.h"
#include "../envmanager_internal.h"

int	envmanager_expand(char **buf)
{
	int		stat;
	char	*backup;

	if (!(*buf))
		return (CODE_ERROR_DATA);
	stat = envmanager_variable_expansion(*buf, &backup);
	if (stat)
		return (stat);
	stat = remove_quotes(&backup);
	if (stat)
	{
		free(backup);
		return (stat);
	}
	free(*buf);
	*buf = backup;
	return (CODE_OK);
}
