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

static int	_do_shell_expansion_abort(char *temp, int stat)
{
	free(temp);
	return (stat);
}

int	do_shell_expansion(char **buf)
{
	int		stat;
	int		option;
	char	*temp;

	temp = ft_strdup(*buf);
	if (!temp)
		return (CODE_ERROR_MALLOC);
	stat = _do_tilde_expansion(&temp);
	if (stat)
		return (_do_shell_expansion_abort(temp, stat));
	option = O_REMQUOTE | O_PARSESQUOTE | O_PARSEDQUOTE | O_REMEMPTYVAR;
	stat = _do_expansion(&temp, option);
	if (stat)
		return (_do_shell_expansion_abort(temp, stat));
	stat = remove_char(&temp, ASCII_DEL);
	if (stat)
		return (_do_shell_expansion_abort(temp, stat));
	free(*buf);
	*buf = temp;
	return (CODE_OK);
}

int	do_shell_expansion_word_split(char *str, char ***split_buf)
{
	int		stat;
	int		option;
	char	*temp;

	temp = ft_strdup(str);
	if (!temp)
		return (CODE_ERROR_MALLOC);
	stat = _do_tilde_expansion(&temp);
	if (stat)
		return (_do_shell_expansion_abort(temp, stat));
	option = O_REMQUOTE | O_PARSESQUOTE | O_PARSEDQUOTE | O_REMEMPTYVAR
		| O_WORDSPLIT;
	stat = _do_expansion(&temp, option);
	if (stat)
		return (_do_shell_expansion_abort(temp, stat));
	stat = _do_word_split(temp, split_buf);
	return (_do_shell_expansion_abort(temp, stat));
}

int	do_heredoc_expansion(char **buf)
{
	int	stat;

	stat = _do_tilde_expansion(buf);
	if (stat)
		return (stat);
	return (_do_expansion(buf, 0));
}
