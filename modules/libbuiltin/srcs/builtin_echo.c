#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "libft_def.h"

static int has_only_ch(char *str, char ch)	
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ch)
			return (FALSE);
	return (TRUE);

}

static int	is_valid_option(char *arg)
{
	if (!arg)
		return (FALSE);
	if (ft_strncmp(arg, "-n", 2) == 0 && has_only_ch(arg + 2, 'n'))
		return (TRUE);
	return (FALSE);
}

static int	builtin_flag_n_on(char *first_arg)
{
	if (!first_arg)
		return (FALSE);
	if (is_valid_option(first_arg))
		return (TRUE);
	return (FALSE);
}

int	builtin_echo(char **argv)
{
	int	flag_n;

	argv++;
	flag_n = builtin_flag_n_on(*argv);
	while (flag_n && is_valid_option(*argv))
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
