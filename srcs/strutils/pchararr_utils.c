#include <stdlib.h>
#include "libft.h"
#include "strutils.h"

char	*pchararr_merge(t_pchararr *strarr)
{
	char	*buf;
	int		i;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	i = 0;
	while (i < strarr->len)
	{
		if (ft_strappend(&buf, (strarr->data)[i]) < 0)
		{
			free(buf);
			return (NULL);
		}
		i++;
	}
	return (buf);
}

void	pchararr_free_all_pchars(t_pchararr *strarr)
{
	int	i;

	i = 0;
	while (i < strarr->len)
	{
		free((strarr->data)[i]);
		i++;
	}
}
