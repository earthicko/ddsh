#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "strutils.h"
#include "expansion_internal.h"

static void	init_skip_envvar(char *str, int *pos, int *start)
{
	(*pos)++;
	*start = *pos;
	if (str[*pos] == '?')
	{
		(*pos)++;
		return ;
	}
	while (
		str[*pos] != '\0'
		&& str[*pos] != '\''
		&& str[*pos] != '\"'
		&& str[*pos] != '$')
		(*pos)++;
}

int	_compose_envvar(
	char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	int		stat;
	char	*varname;
	char	*val;

	init_skip_envvar(str, pos, &start);
	varname = ft_substr(str, start, *pos - start);
	if (!varname)
		return (CODE_ERROR_MALLOC);
	stat = envman_getval(varname, &val);
	free(varname);
	if (stat)
	{
		val = ft_strdup("");
		if (!val)
			return (CODE_ERROR_MALLOC);
	}
	return (_exit_compose(strarr, val));
}

int	_compose_str(char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	char	*word;

	start = *pos;
	while (str[*pos] != '\0'
		&& str[*pos] != '\''
		&& str[*pos] != '\"'
		&& str[*pos] != '$')
		(*pos)++;
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	return (_exit_compose(strarr, word));
}
