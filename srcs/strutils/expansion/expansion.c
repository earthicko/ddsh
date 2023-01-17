#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

static int	exit_shell_expansion(int stat, t_pchararr *strarr, char **buf)
{
	char	*backup;

	if (stat)
	{
		pchararr_free_all_pchars(strarr);
		pchararr_destroy(strarr);
		return (stat);
	}
	backup = pchararr_merge(strarr);
	pchararr_free_all_pchars(strarr);
	pchararr_destroy(strarr);
	if (!backup)
		return (CODE_ERROR_MALLOC);
	free(*buf);
	*buf = backup;
	return (CODE_OK);
}

static int	_compose_char(int *pos, t_pchararr *strarr, char c)
{
	char	*str;

	(*pos)++;
	str = malloc(sizeof(char) * 2);
	if (!str)
		return (CODE_ERROR_MALLOC);
	str[0] = c;
	str[1] = '\0';
	return (_exit_compose(strarr, str));
}

int	_do_shell_expansion(char **buf, int remove_quote, int squote, int dquote)
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
		if ((*buf)[i] == '\'' && squote)
				stat |= _compose_squote((*buf), &i, strarr, remove_quote);
		else if ((*buf)[i] == '\'' && !squote)
				stat |= _compose_char(&i, strarr, '\'');
		else if ((*buf)[i] == '\"' && dquote)
				stat |= _compose_dquote((*buf), &i, strarr, remove_quote);
		else if ((*buf)[i] == '\"' && !dquote)
				stat |= _compose_char(&i, strarr, '\"');
		else if ((*buf)[i] == '$')
			stat |= _compose_envvar((*buf), &i, strarr);
		else
			stat |= _compose_str((*buf), &i, strarr);
	}
	return (exit_shell_expansion(stat, strarr, buf));
}

int	do_shell_expansion(char **buf, int remove_quote)
{
	return (_do_shell_expansion(buf, remove_quote, TRUE, TRUE));
}
