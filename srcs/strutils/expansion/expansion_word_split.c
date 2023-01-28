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

int	*_build_ifs_map(char *str, int len)
{
	int	i;
	int	*map;

	map = malloc(sizeof(int) * len);
	if (!map)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(IFS_DEFAULT, str[i]))
			map[i] = TRUE;
		else
			map[i] = FALSE;
		i++;
	}
	return (map);
}

int	_add_seg_to_arr(t_pchararr *arr, char **str, int **map, int is_ifs)
{
	char	*start;
	char	*seg;

	start = *str;
	while (**str != '\0' && **map == is_ifs)
	{
		(*str)++;
		(*map)++;
	}
	if (is_ifs)
		seg = ft_strdup(SPLIT_MARKER);
	else
		seg = ft_substr(start, 0, *str - start);
	if (!seg)
		return (CODE_ERROR_MALLOC);
	if (pchararr_append(arr, seg))
	{
		free(seg);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

char	*_mark_split_gen_arr(char *str, int *map)
{
	t_pchararr	*arr;
	char		*merged;

	arr = pchararr_create();
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (_add_seg_to_arr(arr, &str, &map, *map))
		{
			pchararr_free_all_pchars(arr);
			pchararr_destroy(arr);
			return (NULL);
		}
	}
	merged = pchararr_merge(arr);
	pchararr_free_all_pchars(arr);
	pchararr_destroy(arr);
	return (merged);
}

int	_mark_split(char **buf)
{
	int		strlen;
	int		*is_ifs;
	char	*marked;

	ft_printf("%s: process %s\n", __func__, *buf);

	strlen = ft_strlen(*buf);
	if (strlen == 0)
		return (CODE_OK);
	is_ifs = _build_ifs_map(*buf, strlen);
	marked = _mark_split_gen_arr(*buf, is_ifs);
	free(is_ifs);
	if (!marked)
		return (CODE_ERROR_MALLOC);
	free(*buf);
	*buf = marked;
	return (CODE_OK);
}

int	_do_word_split(char *str, char ***buf)
{
	(void)str;
	(void)buf;
	return (CODE_OK);
}
