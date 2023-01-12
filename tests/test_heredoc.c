#include <stdio.h>
#include <stdlib.h>
#include "heredoc.h"

int	main(void)
{
	char	*filename;

	heredocmanager(HEREDOCMODE_CLEAR, -1, NULL);
	heredocmanager(HEREDOCMODE_READ, 0, "EOF");
	heredocmanager(HEREDOCMODE_READ, 0, "EOF");
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
