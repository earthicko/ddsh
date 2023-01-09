/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:17:55 by dahkang           #+#    #+#             */
/*   Updated: 2022/08/07 14:55:37 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t	i;

	i = ft_strlen(str) + 1;
	while (--i > 0)
	{
		if (str[i] == (char)ch)
			return ((char *)str + i);
	}
	if (*str == (char)ch)
		return ((char *)str + i);
	return (0);
}
