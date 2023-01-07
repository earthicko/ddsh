/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:23:39 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/31 15:25:04 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ret;
	size_t	size;
	size_t	str_len;

	if (!str)
		return (0);
	str_len = ft_strlen(str);
	if ((size_t)start >= str_len)
		return (ft_strdup(""));
	if (str_len - (size_t)start >= len)
		size = len + 1;
	else
		size = str_len - (size_t)start + 1;
	ret = (char *)malloc(sizeof(char) * (size));
	if (!ret)
		return (0);
	ft_strlcpy(ret, str + start, size);
	return (ret);
}
