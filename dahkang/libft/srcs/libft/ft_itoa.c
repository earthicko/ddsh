/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:46:16 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/21 17:38:32 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 1;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	assign_ret(char *str, int n, int is_neg)
{
	int				i;
	unsigned int	nb;

	if (is_neg)
		nb = -n;
	else
		nb = n;
	i = ft_len(n) + is_neg - 1;
	while (i >= is_neg)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	if (is_neg)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		is_neg;
	int		size;

	if (n < 0)
		is_neg = 1;
	else
		is_neg = 0;
	size = ft_len(n) + is_neg + 1;
	ret = (char *)ft_calloc(size, sizeof(char));
	if (!ret)
		return (0);
	assign_ret(ret, n, is_neg);
	return (ret);
}
