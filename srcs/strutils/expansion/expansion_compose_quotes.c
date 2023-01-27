/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_compose_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "strutils.h"
#include "expansion_internal.h"

static int	_init_compose_squote(int *start, int *pos, char *str, char quote)
{
	*start = *pos;
	(*pos)++;
	while (str[*pos] != '\0' && str[*pos] != quote)
		(*pos)++;
	if (str[*pos] == '\0')
	{
		ft_dprintf(2, "%ssyntax error: unclosed quotes\n", MSG_ERROR_PREFIX);
		return (CODE_ERROR_DATA);
	}
	(*pos)++;
	return (CODE_OK);
}

int	_compose_squote(char *str, int *pos, t_pchararr *strarr, int option)
{
	int		stat;
	int		start;
	char	*word;

	stat = _init_compose_squote(&start, pos, str, '\'');
	if (stat)
		return (stat);
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	if (option & O_REMQUOTE)
	{
		word[0] = ASCII_DEL_CHAR;
		word[ft_strlen(word) - 1] = ASCII_DEL_CHAR;
	}
	return (_exit_compose(strarr, word));
}

static int	_compose_dquote_recurse(char **buf, int option)
{
	int		stat;
	char	*temp[2];

	temp[0] = ft_substr(*buf, 1, ft_strlen(*buf) - 2);
	if (!temp[0])
		return (CODE_ERROR_MALLOC);
	stat = _do_expansion(&(temp[0]), option & O_REMEMPTYVAR);
	if (stat)
	{
		free(temp[0]);
		return (stat);
	}
	temp[1] = ft_strmerge(3, "\"", temp[0], "\"");
	free(temp[0]);
	if (!temp[1])
		return (stat);
	temp[0] = temp[1];
	if (option & O_REMQUOTE)
	{
		temp[0][0] = ASCII_DEL_CHAR;
		temp[0][ft_strlen(temp[0]) - 1] = ASCII_DEL_CHAR;
	}
	free(*buf);
	*buf = temp[0];
	return (CODE_OK);
}

int	_compose_dquote(char *str, int *pos, t_pchararr *strarr, int option)
{
	int		stat;
	int		start;
	char	*word;

	stat = _init_compose_squote(&start, pos, str, '\"');
	if (stat)
		return (stat);
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	stat = _compose_dquote_recurse(&word, option);
	if (stat)
	{
		free(word);
		return (stat);
	}
	return (_exit_compose(strarr, word));
}
