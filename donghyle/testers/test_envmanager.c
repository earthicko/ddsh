#include "envmanager.h"
#include "libft.h"
#include <stdlib.h>

void	get_and_print(char *name)
{
	char	*buf;

	if (envmanager(NULL, &buf, name, NULL))
	{
		ft_printf("no var named %s\n", name);
		return ;
	}
	ft_printf("%s: %s\n", name, buf);
	free(buf);
}

void	test_getenvp(void)
{
	int		stat;
	char	**envp;
	char	**cursor;

	stat = envmanager(NULL, &envp, NULL, NULL);
	if (stat)
	{
		ft_printf("failed to compose envp string\n");
		return ;
	}
	ft_printf("start envp string\n");
	cursor = envp;
	while (*cursor)
	{
		ft_printf("\t%s\n", *cursor);
		cursor++;
	}
	ft_printf("end envp string\n");
	ft_free_strarr(envp);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_getenvp();
	get_and_print("HOME");
	envmanager(envp, NULL, NULL, NULL);
	ft_printf("fuck\n");
	test_getenvp();
	get_and_print("HOME");
	get_and_print("LOGNAME");
	get_and_print("FOO");
	get_and_print("HOME");
	envmanager(NULL, NULL, "FOO", "BAR");
	get_and_print("FOO");
	test_getenvp();
	envmanager(NULL, NULL, "HOME", "BAR");
	get_and_print("HOME");
	test_getenvp();
	envmanager(NULL, NULL, NULL, NULL);
	test_getenvp();
	system("leaks test_envmanager");
	return (0);
}
