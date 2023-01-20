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
	envman_init(envp);
	delim1 = strdup("EO\"F");
	delim2 = strdup("EOF");
	heredoc_read(delim1);
	heredoc_read(delim2);
	free(delim1);
	free(delim2);
	heredoc_get_filename(0, &filename);
	printf("filename: %s\n", filename);
	free(filename);
	heredoc_get_filename(1, &filename);
	printf("filename: %s\n", filename);
	free(filename);
	heredoc_clear(-1);
	system("leaks test_heredoc");
	return (0);
}
