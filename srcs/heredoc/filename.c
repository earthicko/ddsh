/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:53 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "heredoc_internal.h"

static int	_setval_and_return(char **buf, char *val, int ret)
{
	*buf = val;
	return (ret);
}

int	_heredoc_get_filename(char *ttyname, int n_heredoc, int doc_id, char **buf)
{
	char	*docname;
	char	*result;

	if (doc_id < 0 || n_heredoc <= doc_id)
		return (_setval_and_return(buf, NULL, CODE_ERROR_SCOPE));
	docname = ft_itoa(doc_id);
	if (!docname)
		return (_setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	result = ft_strmerge(6, DIR_HEREDOC, "/", PREFIX_HEREDOC_TEMPFILE,
			ttyname, "_", docname);
	free(docname);
	if (!result)
		return (_setval_and_return(buf, NULL, CODE_ERROR_MALLOC));
	return (_setval_and_return(buf, result, CODE_OK));
}

int	_heredoc_get_next_filename(
		char *ttyname, int n_heredoc, int *i_current, char **buf)
{
	int	stat;

	stat = _heredoc_get_filename(ttyname, n_heredoc, *i_current, buf);
	if (!stat)
		(*i_current)++;
	return (stat);
}
