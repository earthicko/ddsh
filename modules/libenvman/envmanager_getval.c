#include "envmanager_internal.h"
#include "libft.h"

int	envmanager_getval(t_list *envlist, char **buf, char *name)
{
	t_enventry	*entry;

	entry = envmanager_getentry(envlist, name);
	if (!entry)
		return (CODE_ERROR_DATA);
	*buf = ft_strdup(entry->val);
	if (!(*buf))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
