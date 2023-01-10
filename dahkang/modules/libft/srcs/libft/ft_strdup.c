/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:50:21 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/16 19:57:30 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(str) + 1;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (0);
	ft_strlcpy(ret, str, size);
	return (ret);
}
