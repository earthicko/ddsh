#include <stddef.h>
#include "libft_def.h"
#include "../envmanager_internal.h"

static int	setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

int	envmanager_expand(char **buf)
{
	int		stat;
	char	*backup;

	if (!(*buf))
		return (CODE_ERROR_DATA);
	backup = *buf;
	stat = envmanager_variable_expansion(*buf, &backup);
	if (stat)
		return (setval_and_return(buf, NULL, stat));
	return (setval_and_return(buf, backup, CODE_OK));
}
