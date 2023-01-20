#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_getenvp(t_list *envlist, char ***buf)
{
	char	**cursor;
	char	*name;
	char	*val;

	*buf = malloc(sizeof(char *) * (ft_lstsize(envlist) + 1));
	if (!(*buf))
		return (CODE_ERROR_MALLOC);
	ft_bzero(*buf, sizeof(char *) * (ft_lstsize(envlist) + 1));
	cursor = *buf;
	while (envlist)
	{
		name = ((t_enventry *)(envlist->content))->name;
		val = ((t_enventry *)(envlist->content))->val;
		*cursor = envman_compose_envstr(name, val);
		if (!(*cursor))
		{
			ft_free_strarr(*buf);
			*buf = NULL;
			return (CODE_ERROR_MALLOC);
		}
		cursor++;
		envlist = envlist->next;
	}
	return (CODE_OK);
}

int	envman_getenvp(char ***buf)
{
	int	stat;

	stat = _envmanager(0, buf, 0, 0);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
