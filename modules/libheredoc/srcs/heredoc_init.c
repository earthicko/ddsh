#include <stdlib.h>
#include "strutils.h"
#include "libft_def.h"
#include "envmanager.h"
#include "heredoc_internal.h"

int	_heredoc_init(int *n_heredoc, int *i_current, char **temp_dir)
{
	char	*home_dir;
	int		stat;

	if (*temp_dir)
		free(*temp_dir);
	*temp_dir = NULL;
	stat = envman_getval("HOME", &home_dir);
	if (stat)
		return (stat);
	stat = ft_strappend(&home_dir, "/");
	if (stat)
	{
		free(home_dir);
		return (stat);
	}
	*temp_dir = home_dir;
	_heredoc_clear(n_heredoc, i_current, *temp_dir, -1);
	return (CODE_OK);
}
