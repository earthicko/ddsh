/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:20:54 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/21 20:00:54 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(int n, int fd)
{
	if (n == 0)
		return ;
	rec(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	ch;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		rec(-(n / 10), fd);
		ch = -(n % 10) + '0';
	}
	else
	{
		rec((n / 10), fd);
		ch = n % 10 + '0';
	}
	ft_putchar_fd(ch, fd);
}
