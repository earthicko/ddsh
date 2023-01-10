#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	builtin_pwd(char **argv)
{
	char	*pwd;
	int		stat;

	while (*argv)
	{
		if ((*argv)[0] == '-')
		{
			// invalid option 에러 처리
			return (1);
		}
		argv++;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	stat = ft_printf("%s\n", pwd);
	free(pwd);
	if (stat < 0)
		return (1);
	return (0);
}
