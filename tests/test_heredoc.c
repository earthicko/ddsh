#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heredoc.h"
#include "envmanager.h"

int	main(int argc, char **argv, char **envp)
{
	char	*filename;
	char	*delim1;
	char	*delim2;

	(void)argc;
	(void)argv;
	envmanager(envp, NULL, NULL, NULL);
	heredocmanager(HEREDOCMODE_CLEAR, -1, NULL);
	delim1 = strdup("EO\"F");
	delim2 = strdup("EOF");
	heredocmanager(HEREDOCMODE_READ, 0, delim1);
	heredocmanager(HEREDOCMODE_READ, 0, delim2);
	free(delim1);
	free(delim2);
	heredocmanager(HEREDOCMODE_GETFILENAME, 0, &filename);
	printf("filename: %s\n", filename);
	free(filename);
	heredocmanager(HEREDOCMODE_GETFILENAME, 1, &filename);
	printf("filename: %s\n", filename);
	free(filename);
	heredocmanager(HEREDOCMODE_CLEAR, -1, NULL);
	system("leaks test_heredoc");
	return (0);
}
