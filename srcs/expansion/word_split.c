/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

int	_do_word_split_addarr_if_notempty(t_pchararr *arr, char **strarr)
{
	char	*str;

	while (*strarr)
	{
		if (ft_strlen(*strarr) > 0)
		{
			if (remove_char(strarr, ASCII_DEL))
				return (CODE_ERROR_MALLOC);
			str = ft_strdup(*strarr);
			if (!str)
				return (CODE_ERROR_MALLOC);
			if (pchararr_append(arr, str))
			{
				free(str);
				return (CODE_ERROR_MALLOC);
			}
		}
		strarr++;
	}
	return (CODE_OK);
}

int	_do_word_split(char *str, t_pchararr **buf)
{
	t_pchararr	*arr;
	char		**temp;

	temp = ft_split_by_chars(str, SPLIT_MARKER);
	if (!temp)
		return (CODE_ERROR_MALLOC);
	arr = pchararr_create();
	if (!arr)
	{
		ft_free_strarr(temp);
		return (CODE_ERROR_MALLOC);
	}
	if (_do_word_split_addarr_if_notempty(arr, temp))
	{
		ft_free_strarr(temp);
		return (CODE_ERROR_MALLOC);
	}
	ft_free_strarr(temp);
	*buf = arr;
	return (CODE_OK);
}
