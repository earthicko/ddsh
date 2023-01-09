/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:36:25 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/17 13:49:06 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		size;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, size);
	ft_strlcat(ret, s2, size);
	return (ret);
}
