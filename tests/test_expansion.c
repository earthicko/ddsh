#include <stdio.h>
#include "envmanager.h"

int	main(int argc, char **argv, char **envp)
{
	char	*word;

	(void)argc;
	(void)argv;
	envmanager(envp, NULL, NULL, NULL);
	word = "en\"vvar$HOME\"FOO$PWD";
	printf("before: %s\n", word);
	printf("exit status %d\n", envmanager_expand(&word));
	printf("after: %s\n", word);
	return (0);
}
