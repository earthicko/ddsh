#include "envmanager_internal.h"
#include "libft.h"
#include <stdlib.h>

static char	*compose_envstr(char *name, char *val)
{
	char	*base;
	char	*temp;

	base = ft_strdup(name);
	if (!base)
		return (NULL);
	temp = ft_strjoin(base, "=");
	free(base);
	if (!temp)
		return (NULL);
	base = temp;
	temp = ft_strjoin(base, val);
	free(base);
	if (!temp)
		return (NULL);
	return (temp);
}

int	envmanager_setval(t_list **envlist, char *name, char *val)
{
	t_enventry	*entry;
	char		*envstr;

	entry = envmanager_getentry(*envlist, name);
	if (entry)
	{
		free(entry->val);
		entry->val = ft_strdup(val);
		if (!(entry->val))
			return (CODE_ERROR_MALLOC);
	}
	else
	{
		envstr = compose_envstr(name, val);
		if (!envstr)
			return (CODE_ERROR_MALLOC);
		envmanager_addentry(envlist, envstr);
		free(envstr);
	}
	return (CODE_OK);
}
