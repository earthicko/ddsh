/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:19 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

static int	_exit_do_expansion(int stat, t_pchararr *strarr, char **buf)
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
	return (remove_char(buf, ASCII_DEL_CHAR));
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

int	_do_expansion(char **buf, int option)
{
	t_pchararr	*words;
	int			i;
	int			stat;

	words = pchararr_create();
	if (!words)
		return (CODE_ERROR_MALLOC);
	i = 0;
	stat = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\'' && (option & O_PARSESQUOTE))
				stat |= _compose_squote((*buf), &i, words, option);
		else if ((*buf)[i] == '\'' && !(option & O_PARSESQUOTE))
				stat |= _compose_char(&i, words, '\'');
		else if ((*buf)[i] == '\"' && (option & O_PARSEDQUOTE))
				stat |= _compose_dquote((*buf), &i, words, option);
		else if ((*buf)[i] == '\"' && !(option & O_PARSEDQUOTE))
				stat |= _compose_char(&i, words, '\"');
		else if ((*buf)[i] == '$')
			stat |= _compose_envvar((*buf), &i, words, option);
		else
			stat |= _compose_str((*buf), &i, words);
	}
	return (_exit_do_expansion(stat, words, buf));
}

int	do_shell_expansion(char **buf)
{
	int	stat;

	stat = _do_tilde_expansion(buf);
	if (stat)
		return (stat);
	return (_do_expansion(buf,
			O_REMQUOTE | O_PARSESQUOTE | O_PARSEDQUOTE | O_REMEMPTYVAR));
}

int	do_heredoc_expansion(char **buf)
{
	int	stat;

	stat = _do_tilde_expansion(buf);
	if (stat)
		return (stat);
	return (_do_expansion(buf, 0));
}
