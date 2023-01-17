#include "libft.h"
#include "envmanager_internal.h"

static int	_envman_getexitstat(char **buf)
{
	char	*backup;

	backup = ft_itoa(exit_stat_manager(-1));
	if (!backup)
		return (CODE_ERROR_MALLOC);
	*buf = backup;
	return (CODE_OK);
}

int	_envman_getval(t_list *envlist, char **buf, char *name)
{
	t_enventry	*entry;
	char		*backup;

	if (ft_strncmp(name, "?", 2) == 0)
		return (_envman_getexitstat(buf));
	entry = _envman_getentry(envlist, name);
	if (!entry)
		return (CODE_ERROR_DATA);
	backup = ft_strdup(entry->val);
	if (!backup)
		return (CODE_ERROR_MALLOC);
	*buf = backup;
	return (CODE_OK);
}

int	envman_getval(char *name, char **buf)
{
	return (_envmanager(0, buf, name, 0));
}
