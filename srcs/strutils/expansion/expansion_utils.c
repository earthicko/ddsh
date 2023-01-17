#include <stdlib.h>
#include "libft.h"
#include "strutils.h"

int	_exit_compose(t_pchararr *strarr, char *word)
{
	int	stat;

	stat = pchararr_append(strarr, word);
	if (stat)
	{
		free(word);
		return (stat);
	}
	return (CODE_OK);
}
