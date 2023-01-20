#include "envmanager_internal.h"
#include "msgdef.h"
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
	int	stat;

	stat = _envmanager(0, 0, name, 0);
	if (stat && stat != CODE_ERROR_DATA)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
