#include "libft.h"
#include "envmanager_internal.h"

int	envman_clear_(t_list **p_list)
{
	if (*p_list)
		ft_lstclear(p_list, free_entry);
	return (CODE_OK);
}

int	envman_clear(void)
{
	return (envmanager(0, 0, 0, 0));
}
