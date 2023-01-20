#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"

static int	export_display(void)
{
	char	**envp;
	char	**cursor;
	char	*pair[2];

	if (envman_getenvp(&envp))
		return (1);
	cursor = envp;
	while (*cursor)
	{
		if (envman_split_envstr(*cursor, &(pair[0]), &(pair[1])))
		{
			ft_free_strarr(envp);
			return (1);
		}
		if (ft_printf("declare -x %s=\"%s\"\n", pair[0], pair[1]) < 0)
		{
			ft_free_strarr(envp);
			return (1);
		}
		free(pair[0]);
		free(pair[1]);
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

	stat = envman_split_envstr(word, &name, &val);
	if (stat)
	{
		if (stat == CODE_ERROR_DATA)
			ft_dprintf(2, "%s: export: `%s': not a valid identifier\n",
				MSG_ERROR_PREFIX, word);
		else if (stat == CODE_ERROR_MALLOC)
			ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (1);
	}
	stat = envman_setval(name, val);
	free(name);
	free(val);
	if (stat)
		return (1);
	return (0);
}

int	builtin_export(char **argv)
{
	int	stat;

	argv++;
	if (!*argv)
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
