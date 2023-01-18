#include <stdlib.h>
#include "executor_internal.h"

void	io_manager(int mode)
{
	static int	backup[2];

	if (mode == STDINOUT_BACKUP)
	{
		backup[0] = dup(STDIN_FILENO);
		backup[1] = dup(STDOUT_FILENO);
		if (backup[0] < 0 || backup[1] < 0)
			exit(EXIT_FAILURE);
	}
	else if (mode == STDINOUT_RESTORE) 
		if (dup2(backup[0], STDIN_FILENO) < 0 || close(backup[0]) < 0
			|| dup2(backup[1], STDOUT_FILENO) < 0 || close(backup[1]) < 0)
			exit(EXIT_FAILURE);
}
