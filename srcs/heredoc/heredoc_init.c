#include <stdlib.h>
#include "strutils.h"
#include "libft_def.h"
#include "envmanager.h"
#include "heredoc_internal.h"

int	heredoc_init_(int *n_heredoc, int *i_current, char **temp_dir)
{
	char	*home_dir;
	int		stat;

	if (*temp_dir)
		free(*temp_dir);
	*temp_dir = NULL;
	stat = envmanager(NULL, &home_dir, "HOME", NULL);
	if (stat)
		return (stat);
	stat = ft_strappend(&home_dir, "/");
	if (stat)
	{
		free(home_dir);
		return (stat);
	}
	*temp_dir = home_dir;
	heredoc_clear_(n_heredoc, i_current, *temp_dir, -1);
	return (CODE_OK);
}
