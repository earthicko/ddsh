#include "envmanager_internal.h"
#include "libft.h"

t_list	*find_list_with_entry(t_list *envlist, char *name)
{
	char	*lstname;

	while (envlist)
	{
		lstname = ((t_enventry *)(envlist->content))->name;
		if (!ft_strncmp(name, lstname, ft_strlen(lstname)))
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}

t_enventry	*envmanager_getentry(t_list *envlist, char *name)
{
	t_list	*list;

	list = find_list_with_entry(envlist, name);
	if (list)
		return (list->content);
	return (NULL);
}

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
