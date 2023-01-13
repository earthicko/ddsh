#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "../envmanager_internal.h"

int	skip_and_append_squote(
		char *str, int *pos, t_pchararr *strarr, int quote_removal)
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
	if (quote_removal && remove_quotes(&word))
	{
		free(word);
		return (CODE_ERROR_MALLOC);
	}
	return (pchararr_append(strarr, word));
}

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
	stat = envmanager(NULL, &val, varname, NULL);
	free(varname);
	if (stat)
	{
		val = ft_strdup("");
		if (!val)
			return (CODE_ERROR_MALLOC);
	}
	return (pchararr_append(strarr, val));
}

int	skip_and_append_str(
		char *str, int *pos, t_pchararr *strarr, int quote_removal)
{
	int		start;
	char	*word;

	start = *pos;
	while (str[*pos] != '\0' && str[*pos] != '\'' && str[*pos] != '$')
		(*pos)++;
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	if (quote_removal && remove_quotes(&word))
	{
		free(word);
		return (CODE_ERROR_MALLOC);
	}
	return (pchararr_append(strarr, word));
}
