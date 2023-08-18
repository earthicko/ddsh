/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

char	*envman_compose_envstr(t_enventry *entry)
{
	return (ft_strmerge(3, entry->name, ENVSTR_DELIM_STR, entry->val));
}

static int	_split_envstr_abort(char **name, char **val, int stat)
{
	if (*name)
		free(*name);
	if (*val)
		free(*val);
	*name = NULL;
	*val = NULL;
	return (stat);
}

int	envman_split_envstr(char *str, char **ret_name, char **ret_val)
{
	size_t	i_split;
	size_t	len_str;

	len_str = ft_strlen(str);
	i_split = ft_strchr(str, ENVSTR_DELIM_CHAR) - str;
	if (i_split == len_str)
		return (CODE_ERROR_DATA);
	*ret_name = ft_substr(str, 0, i_split);
	*ret_val = ft_substr(str, i_split + 1, len_str - i_split - 1);
	if (!(*ret_name && *ret_val))
		return (_split_envstr_abort(ret_name, ret_val, CODE_ERROR_MALLOC));
	if (!is_valid_name(*ret_name))
		return (_split_envstr_abort(ret_name, ret_val, CODE_ERROR_DATA));
	return (CODE_OK);
}
