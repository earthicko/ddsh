#include <unistd.h>
#include "builtin_internal.h"
#include "libft.h"

static int	loop_builtin_echo(char ***p_argv, int *p_flag_n)
{
	if (ft_strncmp(FLAG_N, **p_argv, ft_strlen(FLAG_N)))
	{
		if (ft_printf("%s", **p_argv) < 0)
			return (1);
	}
	else
		*p_flag_n = TRUE;
	(*p_argv)++;
	if (**p_argv)
	{
		if (ft_printf("%c", ' ') < 0)
			return (1);
	}
	else
		return (-1);
	return (0);
}

int	builtin_echo(char **argv)
{
	int	flag_n;
	int	stat;

	flag_n = FALSE;
	while (TRUE)
	{
		stat = loop_builtin_echo(&argv, &flag_n);
		if (stat == -1)
			break ;
		if (stat == 1)
			return (1);
	}
	if (!flag_n)
	{
		if (ft_printf("%c", '\n') < 0)
			return (1);
	}
	return (0);
}
