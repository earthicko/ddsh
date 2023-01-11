#include "libft_def.h"
#include "envmanager_internal.h"

int	envman_init(t_list **p_list, char **envp)
{
	int	stat;

	if (*p_list)
		envman_clear(p_list);
	while (*envp)
	{
		stat = envman_addentry(p_list, *envp);
		if (stat)
		{
			envman_clear(p_list);
			return (stat);
		}
		envp++;
	}
	return (CODE_OK);
}
