#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutils.h"
#include "envmanager.h"

void	set_commandnames(char **commandnames)
{
	commandnames[0] = strdup("cd");
	commandnames[1] = strdup("echo");
	commandnames[2] = strdup("export");
	commandnames[3] = strdup("pwd");
	commandnames[4] = strdup("unset");
	commandnames[5] = strdup("env");
	commandnames[6] = strdup("exit");
	commandnames[7] = strdup(" cd");
	commandnames[8] = strdup("echo ");
	commandnames[9] = strdup("expo rt");
	commandnames[10] = strdup("./Makefile");
	commandnames[11] = strdup("./Makefi");
	commandnames[12] = strdup("bash");
	commandnames[13] = strdup("env");
	commandnames[14] = strdup("brew");
	commandnames[15] = strdup("/bin/bash");
	commandnames[16] = strdup("/bin/bashes");
}

void	set_words(char **words)
{
	words[0] = strdup("\"abc\"defg\"\"hi\"");
	words[1] = strdup("abc\"\"\"\"defg\"\"hi");
	words[2] = strdup("\"abc\"defg\"\"hi\"\"\"\"");
	words[3] = strdup("\"\"\"\"\"abc\"defg\"\"hi");
	words[4] = strdup("abcdefghi");
}

void	test_is_builtin_command(char **commandnames)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		printf("is_builtin_command: %s: %d\n",
			commandnames[i], is_builtin_command(commandnames[i]));
		i++;
	}
}

void	test_find_exec(char **commandnames)
{
	int	i;
	int	stat;

	i = 0;
	while (i < 17)
	{
		printf("find_exec: ");
		stat = find_exec(&(commandnames[i]));
		if (stat == 1)
			printf("%s is builtin\n", commandnames[i]);
		else if (stat == 0)
			printf("%s exists in literal path\n", commandnames[i]);
		else
			printf("%s not found\n", commandnames[i]);
		i++;
	}
}

void	test_remove_quotes(char **words)
{
	int	i;
	int	stat;

	i = 0;
	while (i < 5)
	{
		stat = remove_quotes(&(words[i]));
		printf("remove_quotes stat %d result %s\n", stat, words[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*commandnames[100];
	char	*words[100];

	(void)argc;
	(void)argv;
	envman_init(envp);
	set_commandnames(commandnames);
	set_words(words);
	test_is_builtin_command(commandnames);
	test_find_exec(commandnames);
	test_remove_quotes(words);
	system("leaks test_strutils");
	return (0);
}
