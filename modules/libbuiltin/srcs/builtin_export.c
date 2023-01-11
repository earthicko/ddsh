#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "builtin_internal.h"

static int	export_display(void)
{
	char	**envp;
	char	**cursor;
	char	*name;
	char	*val;

	if (envmanager(NULL, &envp, NULL, NULL))
		return (1);
	cursor = envp;
	while (*cursor)
	{
		if (envman_split_envstr(*cursor, &name, &val))
		{
			ft_free_strarr(envp);
			return (1);
		}
		ft_printf(FMTSTR_EXPORT, name, val);
		free(name);
		free(val);
		cursor++;
	}
	ft_free_strarr(envp);
	return (0);
}

static int	export_var(char *word)
{
	char	*name;
	char	*val;
	int		stat;

	if (envman_split_envstr(word, &name, &val))
		return (1);
	stat = envmanager(NULL, NULL, name, val);
	free(name);
	free(val);
	return (stat);
}

int	builtin_export(char **argv)
{
	int	stat;

	if (!(argv[0]))
		return (export_display());
	stat = 0;
	while (*argv)
	{
		if (export_var(*argv))
			stat = 1;
		argv++;
	}
	return (stat);
}
