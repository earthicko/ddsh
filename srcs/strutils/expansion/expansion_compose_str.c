/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_compose_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "strutils.h"
#include "msgdef.h"
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
	if (str[*pos] == '{')
	{
		while (!(str[*pos] == '}' || str[*pos] == '\0'))
			(*pos)++;
		if (str[*pos] == '}')
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

static char	*_compose_envvar_varname(char *str, int start, int end)
{
	if (str[start] == '{')
	{
		if (str[end - 1] != '}')
		{
			ft_dprintf(2, "%svalue name unclosed with `}'\n", MSG_ERROR_PREFIX);
			return (NULL);
		}
		return (ft_substr(str, start + 1, end - start - 2));
	}
	return (ft_substr(str, start, end - start));
}

int	_compose_envvar(
	char *str, int *pos, t_pchararr *strarr, int option)
{
	int		start;
	int		stat;
	char	*varname;
	char	*val;

	_init_compose_envvar(str, pos, &start);
	varname = _compose_envvar_varname(str, start, *pos);
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
