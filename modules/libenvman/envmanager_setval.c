#include "envmanager_internal.h"
#include "libft.h"
#include <stdlib.h>

int	envmanager_setval(t_list **envlist, char *name, char *val)
{
	t_enventry	*entry;
	char		*envstr;
	char		*temp;
	int			stat;

	entry = envmanager_getentry(*envlist, name);
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
		envstr = compose_envstr(name, val);
		if (!envstr)
			return (CODE_ERROR_MALLOC);
		stat = envmanager_addentry(envlist, envstr);
		free(envstr);
		if (stat)
			return (stat);
	}
	return (CODE_OK);
}
