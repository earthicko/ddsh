#include "envmanager_internal.h"
#include "libft.h"

int	_envman_unsetval(t_list **envlist, char *name)
{
	t_list	*list;

	list = _find_list_with_entry(*envlist, name);
	if (!list)
		return (CODE_ERROR_DATA);
	ft_lstunlink(envlist, list, _free_entry);
	return (CODE_OK);
}

int	envman_unsetval(char *name)
{
	return (_envmanager(0, 0, name, 0));
}
