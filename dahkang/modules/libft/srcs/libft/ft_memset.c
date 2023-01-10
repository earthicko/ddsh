/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:50:57 by dahkang           #+#    #+#             */
/*   Updated: 2022/08/07 14:56:54 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)ptr)[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
