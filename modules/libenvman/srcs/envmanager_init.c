#include "libft_def.h"
#include "envmanager_internal.h"

int	envman_init_(t_list **p_list, char **envp)
{
	int	stat;

	if (*p_list)
		envman_clear_(p_list);
	while (*envp)
	{
		stat = envman_addentry(p_list, *envp);
		if (stat)
		{
			envman_clear_(p_list);
			return (stat);
		}
		envp++;
	}
	return (CODE_OK);
}

int	envman_init(char **envp)
{
	return (envmanager(envp, 0, 0, 0));
}
