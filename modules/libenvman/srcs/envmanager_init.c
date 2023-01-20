#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_init(t_list **p_list, char **envp)
{
	int	stat;

	if (*p_list)
		_envman_clear(p_list);
	while (*envp)
	{
		stat = _envman_addentry(p_list, *envp);
		if (stat)
		{
			_envman_clear(p_list);
			return (stat);
		}
		envp++;
	}
	return (CODE_OK);
}

int	envman_init(char **envp)
{
	int	stat;

	stat = _envmanager(envp, 0, 0, 0);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
