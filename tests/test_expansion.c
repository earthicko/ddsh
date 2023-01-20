#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "envmanager.h"
#include "strutils.h"

void	test_expansion(char *str, int mode)
{
	int		stat;
	char	*echo_str;

	str = strdup(str);
	echo_str = ft_strmerge(3, "echo \"", str, "\"");
	printf("before: <%s>\n", str);
	if (!mode)
		stat = do_shell_expansion(&str);
	else
		stat = do_heredoc_expansion(&str);
	printf("after:  <%s>\n", str);
	printf("exit status %d\n", stat);
	free(str);
	free(echo_str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*execname;

	(void)argc;
	(void)argv;
	envman_init(envp);
	envman_setval("QUOTESVAL", "VAL\"\'VAL");
	test_expansion("en\"vvar$HOME\"FO'O$PWD'   aa'$?'$?$\"?\"\"$\"?aa", 0);
	test_expansion("en\"vvar$HOME\"FO'O$PWD'   aa'$?'$?$\"?\"\"$\"?aa", 1);
	test_expansion("quotesval$QUOTESVAL\"quotes\"quotes\"$QUOTESVAL\"", 0);
	test_expansion("quotesval$QUOTESVAL\"quotes\"quotes\"$QUOTESVAL\"", 1);
	test_expansion("abc\"de\'fg\'hijkl\"mnop", 0);
	test_expansion("abc\"de\'fg\'hijkl\"mnop", 1);
	test_expansion("abc\"de\'fg\"hijkl\'mnop", 0);
	test_expansion("abc\"de\'fg\"hijkl\'mnop", 1);
	test_expansion("$\"\"", 0);
	test_expansion("$\"\"", 1);
	test_expansion("$123PATH", 0);
	test_expansion("$123PATH", 1);
	test_expansion("$", 0);
	test_expansion("$", 1);
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
