#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "envmanager.h"
#include "strutils.h"

int	main(int argc, char **argv, char **envp)
{
	char	*word;
	char	*execname;

	(void)argc;
	(void)argv;
	envmanager(envp, NULL, NULL, NULL);
	word = strdup("en\"vvar$HOME\"FO'O$PWD'   aa'$?'$?$\"?\"\"$\"?aa");
	printf("before: <%s>\n", word);
	printf("exit status %d\n", envmanager_replace_envvar(&word, 0));
	printf("after: <%s>\n", word);
	free(word);
	execname = strdup("brew");
	printf("before: <%s>\n", execname);
	find_exec(&execname);
	printf("after: <%s>\n", execname);
	free(execname);
	execname = strdup("export");
	printf("exit status %d\n", find_exec(&execname));
	free(execname);
	system("leaks test_expansion");
	return (0);
}
