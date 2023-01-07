/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:03:05 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/31 15:31:38 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_cnt(char const *str, char ch)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		while (*str && *str == ch)
			str++;
		if (*str && *str != ch)
		{
			cnt++;
			while (*str && *str != ch)
				str++;
		}
	}
	return (cnt);
}

static char	**free_alloc(char **ptr, int i)
{
	while (--i >= 0)
	{
		free(ptr[i]);
		ptr[i] = 0;
	}
	free(ptr);
	ptr = 0;
	return (0);
}

char	**ft_split(char const *str, char ch)
{
	char	**ret;
	char	*from;
	int		i;

	if (!str)
		return (0);
	i = 0;
	ret = (char **)ft_calloc((ft_word_cnt(str, ch) + 1), sizeof(char *));
	if (!ret)
		return (0);
	while (*str)
	{
		while (*str && *str == ch)
			str++;
		if (*str && *str != ch)
		{
			from = (char *)str;
			while (*str && *str != ch)
				str++;
			ret[i] = ft_substr(from, 0, str - from);
			if (!ret[i++])
				return (free_alloc(ret, i));
		}
	}
	return (ret);
}
