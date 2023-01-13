#include <stdio.h>
#include <unistd.h>
#include "builtin_internal.h"
#include "libft.h"

static int	builtin_flag_n_on(char *first_arg)
{
	if (!first_arg)
		return (FALSE);
	if (ft_strncmp(FLAG_N, first_arg, ft_strlen(FLAG_N) + 1))
		return (FALSE);
	return (TRUE);
}

int	builtin_echo(char **argv)
{
	int	flag_n;

	flag_n = builtin_flag_n_on(*argv);
	while (*argv)
	{
		if (printf("%s", *argv) < 0)
			return (1);
		argv++;
		if (*argv)
		{
			if (printf("%c", ' ') < 0)
				return (1);
		}
	}
	if (!flag_n)
	{
		if (printf("%c", '\n') < 0)
			return (1);
	}
	return (0);
}
