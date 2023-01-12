#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "../envmanager_internal.h"

static char	*merge_pchararr(t_pchararr *strarr)
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

static void	init_variable_expansion(t_pchararr **strarr, int *i, int *stat)
{
	*strarr = pchararr_create();
	*stat = 0;
	*i = 0;
}

int	envmanager_variable_expansion(char *input, char **buf)
{
	t_pchararr	*strarr;
	int			i;
	int			stat;

	init_variable_expansion(&strarr, &i, &stat);
	if (!strarr)
		return (CODE_ERROR_MALLOC);
	while (input[i])
	{
		if (input[i] == '\'')
			stat = stat | skip_and_append_squote(input, &i, strarr);
		else if (input[i] == '$')
			stat = stat | skip_and_append_envvar(input, &i, strarr);
		else
			stat = stat | skip_and_append_str(input, &i, strarr);
	}
	if (stat)
	{
		pchararr_destroy(strarr);
		return (stat);
	}
	*buf = merge_pchararr(strarr);
	if (!(*buf))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
