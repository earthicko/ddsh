#include "envmanager_internal.h"
#include "libft.h"
#include <stdlib.h>

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

static void	free_entry(void *content)
{
	enventry_destroy(content);
}

static int	envmanager_clear(t_list **p_list)
{
	if (*p_list)
		ft_lstclear(p_list, free_entry);
	return (CODE_OK);
}

static int	envmanager_init(t_list **p_list, char **envp)
{
	int	stat;

	if (*p_list)
		envmanager_clear(p_list);
	while (*envp)
	{
		stat = envmanager_addentry(p_list, *envp);
		if (stat)
		{
			envmanager_clear(p_list);
			return (stat);
		}
		envp++;
	}
	return (CODE_OK);
}

// init: set envp
// clear: set none
// getval: set (char **)buf, name
// setval: set name, val
// getenvp: set (char ***)buf
int	envmanager(char **envp, void *buf, char *name, char *val)
{
	static t_list	*envlist;

	if (envp && !buf && !name && !val)
		return (envmanager_init(&envlist, envp));
	else if (!envp && !buf && !name && !val)
		return (envmanager_clear(&envlist));
	else if (!envp && buf && name && !val)
		return (envmanager_getval(envlist, buf, name));
	else if (!envp && !buf && name && val)
		return (envmanager_setval(&envlist, name, val));
	else if (!envp && buf && !name && !val)
		return (envmanager_getenvp(envlist, buf));
	return (CODE_ERROR_DATA);
}
