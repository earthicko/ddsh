#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "envmanager.h"

int	main(int argc, char **argv, char **envp)
{
	char	*word;

	(void)argc;
	(void)argv;
	envmanager(envp, NULL, NULL, NULL);
	word = strdup("en\"vvar$HOME\"FO'O$PWD'");
	printf("before: <%s>\n", word);
	printf("exit status %d\n", envmanager_replace_envvar(&word, 0));
	printf("after: <%s>\n", word);
	free(word);
	system("leaks test_expansion");
	return (0);
}
