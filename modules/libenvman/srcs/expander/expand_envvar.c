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

static void	free_all_pchararr(t_pchararr *strarr)
{
	int	i;

	i = 0;
	while (i < strarr->len)
	{
		free((strarr->data)[i]);
		i++;
	}
}

static int	exit_replace_envvar(int stat, t_pchararr *strarr, char **buf)
{
	char	*backup;

	if (stat)
	{
		pchararr_destroy(strarr);
		return (stat);
	}
	backup = merge_pchararr(strarr);
	free_all_pchararr(strarr);
	pchararr_destroy(strarr);
	if (!backup)
		return (CODE_ERROR_MALLOC);
	free(*buf);
	*buf = backup;
	return (CODE_OK);
}

int	envmanager_replace_envvar(char **buf, int quote_removal)
{
	t_pchararr	*strarr;
	int			i;
	int			stat;

	strarr = pchararr_create();
	if (!strarr)
		return (CODE_ERROR_MALLOC);
	i = 0;
	stat = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\'')
			stat = stat | skip_and_append_squote(
					(*buf), &i, strarr, quote_removal);
		else if ((*buf)[i] == '$')
			stat = stat | skip_and_append_envvar(
					(*buf), &i, strarr);
		else
			stat = stat | skip_and_append_str(
					(*buf), &i, strarr, quote_removal);
	}
	return (exit_replace_envvar(stat, strarr, buf));
}
