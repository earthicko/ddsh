#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "strutils.h"
#include "expansion_internal.h"

static void	_init_compose_envvar(char *str, int *pos, int *start)
{
	(*pos)++;
	*start = *pos;
	if (str[*pos] == '?')
	{
		(*pos)++;
		return ;
	}
	if (ft_isdigit(str[*pos]))
		return ;
	while (ft_isalnum(str[*pos]) || str[*pos] == '_')
		(*pos)++;
}

static int	_handle_empty_varname(t_pchararr *strarr, char *varname)
{
	char	*val;

	free(varname);
	val = ft_strdup("$");
	if (!val)
		return (CODE_ERROR_MALLOC);
	return (_exit_compose(strarr, val));
}

int	_compose_envvar(
	char *str, int *pos, t_pchararr *strarr, int option)
{
	int		start;
	int		stat;
	char	*varname;
	char	*val;

	_init_compose_envvar(str, pos, &start);
	varname = ft_substr(str, start, *pos - start);
	if (!varname)
		return (CODE_ERROR_MALLOC);
	if (ft_strlen(varname) == 0
		&& (!(option & O_REMEMPTYVAR) || str[*pos] == '\0'))
		return (_handle_empty_varname(strarr, varname));
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
