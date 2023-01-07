/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:51:16 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/16 18:57:01 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t n)
{
	while (n && *(unsigned char *)str != (unsigned char)ch)
	{
		str++;
		n--;
	}
	if (n && *(unsigned char *)str == (unsigned char)ch)
		return ((void *)str);
	else
		return (0);
}
