#include "envmanager_internal.h"
#include "libft.h"

int	envman_unsetval_(t_list **envlist, char *name)
{
	t_list	*list;

	list = find_list_with_entry(*envlist, name);
	if (!list)
		return (CODE_ERROR_DATA);
	ft_lstunlink(envlist, list, free_entry);
	return (CODE_OK);
}

int	envman_unsetval(char *name)
{
	return (envmanager(0, 0, name, 0));
}
