#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

t_enventry	*enventry_destroy(t_enventry *enventry)
{
	if (!enventry)
		return (NULL);
	if (enventry->name)
		free(enventry->name);
	if (enventry->val)
		free(enventry->val);
	free(enventry);
	return (NULL);
}

void	free_entry(void *content)
{
	enventry_destroy(content);
}

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

int	envmanager_addentry(t_list **p_list, char *env)
{
	t_list		*newlst;
	t_enventry	*entry;
	int			stat;

	entry = malloc(sizeof(t_enventry));
	if (!entry)
		return (CODE_ERROR_MALLOC);
	ft_memset(entry, 0, sizeof(entry));
	stat = split_envstring(env, &(entry->name), &(entry->val));
	if (stat)
	{
		enventry_destroy(entry);
		return (stat);
	}
	newlst = ft_lstnew(entry);
	if (!newlst)
	{
		enventry_destroy(entry);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(p_list, newlst);
	return (CODE_OK);
}
