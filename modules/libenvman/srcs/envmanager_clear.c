#include "libft.h"
#include "envmanager_internal.h"

int	_envman_clear(t_list **p_list)
{
	if (*p_list)
		ft_lstclear(p_list, _free_entry);
	return (CODE_OK);
}

int	envman_clear(void)
{
	return (_envmanager(0, 0, 0, 0));
}
