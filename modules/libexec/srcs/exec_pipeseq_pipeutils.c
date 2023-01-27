#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"

void	exec_pipeseq_destroy_pipes(int *pipes, int n_pipes)
{
	int	i;
	int	*cursor;

	cursor = pipes;
	i = 0;
	while (i < n_pipes)
	{
		close(cursor[0]);
		close(cursor[1]);
		cursor += 2;
		i++;
	}
	free(pipes);
}

int	exec_pipeseq_create_pipes(int **pipes, int n)
{
	int	i;
	int	*cursor;

	*pipes = malloc(sizeof(int) * (2 * n));
	if (!*pipes)
		return (CODE_ERROR_MALLOC);
	cursor = *pipes;
	i = 0;
	while (i < n)
	{
		if (pipe(cursor))
		{
			ft_dprintf(2, "%sfailed to deploy pipe.\n", MSG_ERROR_PREFIX);
			exec_pipeseq_destroy_pipes(*pipes, i);
			return (CODE_ERROR_IO);
		}
		ft_dprintf(2, "pipe created %d %d\n", cursor[0], cursor[1]);
		cursor += 2;
		i++;
	}

	for (int i = 0; i < n * 2; i++)
		ft_dprintf(2, "%d ", (*pipes)[i]);
	ft_dprintf(2,"\n");
	return (CODE_OK);
}
