/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:19:20 by dahkang           #+#    #+#             */
/*   Updated: 2022/08/07 14:57:14 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ret;

	ret = dst;
	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	else
	{
		dst += len - 1;
		src += len - 1;
		while (len--)
			*(unsigned char *)dst-- = *(const unsigned char *)src--;
	}
	return (ret);
}
