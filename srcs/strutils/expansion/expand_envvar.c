#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

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

static int	exit_shell_expansion(int stat, t_pchararr *strarr, char **buf)
{
	char	*backup;

	if (stat)
	{
		free_all_pchararr(strarr);
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

int	do_shell_expansion(char **buf, int remove_quote, int squote, int dquote)
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
		if (squote && (*buf)[i] == '\'')
			stat |= skip_and_append_squote(
					(*buf), &i, strarr, remove_quote);
		else if (dquote && (*buf)[i] == '\"')
			stat |= skip_and_append_dquote(
					(*buf), &i, strarr, remove_quote);
		else if ((*buf)[i] == '$')
			stat |= skip_and_append_envvar(
					(*buf), &i, strarr);
		else
			stat |= skip_and_append_str(
					(*buf), &i, strarr, remove_quote);
	}
	return (exit_shell_expansion(stat, strarr, buf));
}
