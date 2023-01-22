#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"

int	builtin_env(char **argv)
{
	char	**envp;
	char	**cursor;
	int		stat;

	(void)argv;
	if (envman_getenvp(&envp))
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (1);
	}
	stat = 0;
	cursor = envp;
	while (*cursor)
	{
		if (ft_printf("%s\n", *cursor) < 0)
			stat = 1;
		cursor++;
	}
	ft_free_strarr(envp);
	return (stat);
}
