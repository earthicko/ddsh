#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_setval(t_list **envlist, char *name, char *val)
{
	t_enventry	*entry;
	char		*envstr;
	char		*temp;
	int			stat;

	entry = _envman_getentry(*envlist, name);
	if (entry)
	{
		temp = ft_strdup(val);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		free(entry->val);
		entry->val = temp;
	}
	else
	{
		envstr = envman_compose_envstr(name, val);
		if (!envstr)
			return (CODE_ERROR_MALLOC);
		stat = _envman_addentry(envlist, envstr);
		free(envstr);
		if (stat)
			return (stat);
	}
	return (CODE_OK);
}

int	envman_setval(char *name, char *val)
{
	int	stat;

	stat = _envmanager(0, 0, name, val);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
