#include "envmanager.h"
#include <stdlib.h>
#include <stdio.h>

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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	envmanager(envp, NULL, NULL, NULL);
	get_and_print("HOME");
	get_and_print("LOGNAME");
	get_and_print("FOO");
	get_and_print("HOME");
	envmanager(NULL, NULL, "FOO", "BAR");
	get_and_print("FOO");
	envmanager(NULL, NULL, "HOME", "BAR");
	get_and_print("HOME");
	envmanager(NULL, NULL, NULL, NULL);
	system("leaks test_envmanager");
	return (0);
}
