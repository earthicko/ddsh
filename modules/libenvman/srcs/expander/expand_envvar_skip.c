#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "../envmanager_internal.h"

int	skip_and_append_squote(char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	char	*word;

	start = *pos;
	(*pos)++;
	while (str[*pos] != '\'')
		(*pos)++;
	(*pos)++;
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	ft_printf("%s: made <%s>\n", __func__, word);
	if (pchararr_append(strarr, word))
	{
		free(word);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

static void	init_skip_envvar(char *str, int *pos, int *start)
{
	(*pos)++;
	*start = *pos;
	while (
		str[*pos] != '\0'
		&& str[*pos] != '\''
		&& str[*pos] != '\"'
		&& str[*pos] != '$')
		(*pos)++;
}

int	skip_and_append_envvar(char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	int		stat;
	char	*varname;
	char	*val;

	init_skip_envvar(str, pos, &start);
	varname = ft_substr(str, start, *pos - start);
	if (!varname)
		return (CODE_ERROR_MALLOC);
	ft_printf("%s: envvar name <%s>\n", __func__, varname);
	stat = envmanager(NULL, &val, varname, NULL);
	free(varname);
	if (stat)
	{
		val = ft_strdup("");
		if (!val)
			return (CODE_ERROR_MALLOC);
	}
	if (pchararr_append(strarr, val))
	{
		free(val);
		return (CODE_ERROR_MALLOC);
	}
	ft_printf("%s: envvar val <%s>\n", __func__, val);
	return (CODE_OK);
}

int	skip_and_append_str(char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	char	*word;

	start = *pos;
	while (str[*pos] != '\0' && str[*pos] != '\'' && str[*pos] != '$')
		(*pos)++;
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	ft_printf("%s: made <%s>\n", __func__, word);
	if (pchararr_append(strarr, word))
	{
		free(word);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}
