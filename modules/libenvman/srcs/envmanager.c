#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

// init: set envp
// clear: set none
// getval: set (char **)buf, name
// setval: set name, val
// unsetval: set name
// getenvp: set (char ***)buf
int	envmanager(char **envp, void *buf, char *name, char *val)
{
	static t_list	*envlist;

	if (envp && !buf && !name && !val)
		return (envman_init_(&envlist, envp));
	else if (!envp && !buf && !name && !val)
		return (envman_clear_(&envlist));
	else if (!envp && buf && name && !val)
		return (envman_getval_(envlist, buf, name));
	else if (!envp && !buf && name && val)
		return (envman_setval_(&envlist, name, val));
	else if (!envp && !buf && name && !val)
		return (envman_unsetval_(&envlist, name));
	else if (!envp && buf && !name && !val)
		return (envman_getenvp_(envlist, buf));
	return (CODE_ERROR_DATA);
}
