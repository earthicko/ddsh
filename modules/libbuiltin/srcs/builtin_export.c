#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "envmanager.h"

static int	export_display(void)
{
	char	**envp;
	char	**cursor;
	char	*name;
	char	*val;

	if (envman_getenvp(&envp))
		return (1);
	cursor = envp;
	while (*cursor)
	{
		if (envman_split_envstr(*cursor, &name, &val))
		{
			ft_free_strarr(envp);
			return (1);
		}
		printf("declare -x %s=\"%s\"\n", name, val);
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
	stat = envman_setval(name, val);
	free(name);
	free(val);
	return (stat);
}

// TODO: 모든 환경변수를 언셋했을 때, export가 제대로 되는지 확인
// TODO: export에 비정상적인 argv가 들어오는 경우에 대한 로직 추가(잘못된 사용)
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
