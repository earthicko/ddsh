#include <stdlib.h>
#include <stdio.h>
#include "envmanager.h"
#include "libft.h"

void	get_and_print(char *name)
{
	char	*buf;

	if (envmanager(NULL, &buf, name, NULL))
	{
		printf("no var named %s\n", name);
		return ;
	}
	printf("%s: %s\n", name, buf);
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
		printf("failed to compose envp string\n");
		return ;
	}
	printf("start envp string\n");
	cursor = envp;
	while (*cursor)
	{
		printf("\t%s\n", *cursor);
		cursor++;
	}
	printf("end envp string\n");
	ft_free_strarr(envp);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_getenvp();
	get_and_print("HOME");
	envmanager(envp, NULL, NULL, NULL);
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
