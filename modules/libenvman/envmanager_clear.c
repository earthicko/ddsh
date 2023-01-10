#include "envmanager_internal.h"
#include "libft.h"

int	envmanager_clear(t_list **p_list)
{
	if (*p_list)
		ft_lstclear(p_list, free_entry);
	return (CODE_OK);
}
