#include "libft.h"
#include "envmanager_internal.h"

int	envmanager_unsetval(t_list **envlist, char *name)
{
	t_list	*list;

	list = find_list_with_entry(*envlist, name);
	if (list)
		ft_lstunlink(envlist, list, free_entry);
	return (CODE_OK);
}
