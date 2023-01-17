#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

static int	init_skip_and_append_quote(
		int	*start, int *pos, char *str, char quote)
{
	*start = *pos;
	(*pos)++;
	while (str[*pos] != '\0' && str[*pos] != quote)
		(*pos)++;
	if (str[*pos] == '\0')
	{
		ft_printf("%s: Unimplemented error msg\n", __func__);
		return (CODE_ERROR_DATA);
	}
	(*pos)++;
	return (CODE_OK);
}

int	_compose_squote(
		char *str, int *pos, t_pchararr *strarr, int remove_quote)
{
	int		stat;
	int		start;
	char	*word;
	char	*temp;

	stat = init_skip_and_append_quote(&start, pos, str, '\'');
	if (stat)
		return (stat);
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	if (remove_quote)
	{
		temp = ft_substr(word, 1, ft_strlen(word) - 2);
		free(word);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		word = temp;
	}
	return (_exit_compose(strarr, word));
}

static int	skip_and_append_dquote_recurse(char **buf, int remove_quote)
{
	int		stat;
	char	*temp[2];

	temp[0] = ft_substr(*buf, 1, ft_strlen(*buf) - 2);
	if (!temp[0])
		return (CODE_ERROR_MALLOC);
	stat = _do_shell_expansion(&(temp[0]), FALSE, FALSE, FALSE);
	if (stat)
	{
		free(temp[0]);
		return (stat);
	}
	if (!remove_quote)
	{
		temp[1] = ft_strmerge(3, "\"", temp[0], "\"");
		free(temp[0]);
		if (!temp[1])
			return (stat);
		temp[0] = temp[1];
	}
	free(*buf);
	*buf = temp[0];
	return (CODE_OK);
}

int	_compose_dquote(
		char *str, int *pos, t_pchararr *strarr, int remove_quote)
{
	int		stat;
	int		start;
	char	*word;

	stat = init_skip_and_append_quote(&start, pos, str, '\"');
	if (stat)
		return (stat);
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	stat = skip_and_append_dquote_recurse(&word, remove_quote);
	if (stat)
	{
		free(word);
		return (stat);
	}
	return (_exit_compose(strarr, word));
}
