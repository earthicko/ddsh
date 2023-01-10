#include "envmanager_internal.h"
#include "libft.h"

int	envmanager_unsetval(t_list **envlist, char *name)
{
	t_list	*list;

	list = find_list_with_entry(*envlist, name);
	if (!list)
		return (CODE_ERROR_DATA);
	ft_lstunlink(envlist, list, free_entry);
	return (CODE_OK);
}
