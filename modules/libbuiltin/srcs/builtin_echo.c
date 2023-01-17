#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static int	builtin_flag_n_on(char *first_arg)
{
	if (!first_arg)
		return (FALSE);
	if (ft_strncmp("-n", first_arg, 3))
		return (FALSE);
	return (TRUE);
}

int	builtin_echo(char **argv)
{
	int	flag_n;

	argv++;
	flag_n = builtin_flag_n_on(*argv);
	if (flag_n)
		argv++;
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
