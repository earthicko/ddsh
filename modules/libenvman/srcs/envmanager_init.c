#include "libft_def.h"
#include "envmanager_internal.h"

int	envmanager_init(t_list **p_list, char **envp)
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
