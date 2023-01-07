/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:39:31 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/30 20:57:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	src_idx;

	src_len = ft_strlen(src);
	if (!dst && !dst_size)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= dst_size)
		return (src_len + dst_size);
	src_idx = 0;
	while (src[src_idx] && src_idx + dst_len + 1 < dst_size)
	{
		dst[dst_len + src_idx] = src[src_idx];
		src_idx++;
	}
	dst[dst_len + src_idx] = 0;
	return (dst_len + src_len);
}
