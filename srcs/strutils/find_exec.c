#include "libft.h"
#include "strutils.h"
#include "envmanager.h"

static int	find_exec_from_path(char **buf)
{
	(void)buf;
	ft_printf("Unimplemented stub of find_exec_from_path.\n");
	return (CODE_OK);
}

// if builtin, return 1. else replace word with absolute path and return 0.
// if not found in path return CODE_ERROR_GENERIC.
int	find_exec(char **buf)
{
	if (!(*buf))
		return (CODE_ERROR_DATA);
	if (is_builtin_command(*buf))
		return (1);
	if (ft_strchr(*buf, '/'))
		return (CODE_OK);
	return (find_exec_from_path(buf));
}
