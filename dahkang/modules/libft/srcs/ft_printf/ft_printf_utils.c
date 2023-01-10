/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:45:32 by dahkang           #+#    #+#             */
/*   Updated: 2022/10/03 22:55:24 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	pf_len(int n)
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

void	pf_itoa_hex(unsigned long long n, char str[], char specifier)
{
	unsigned long long	nb;
	int					i;

	nb = n;
	i = 1;
	while (n / 16)
	{
		i++;
		n /= 16;
	}
	str[i] = 0;
	while (--i >= 0)
	{
		if (specifier == 'x')
			str[i] = "0123456789abcdef"[nb % 16];
		else if (specifier == 'X')
			str[i] = "0123456789ABCDEF"[nb % 16];
		nb /= 16;
	}
}

void	pf_itoa(int n, char str[])
{
	int				i;
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	i = pf_len(n) + (n < 0);
	str[i] = 0;
	while (--i >= (n < 0))
	{
		str[i] = "0123456789"[nb % 10];
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
}

void	pf_itoa_u(unsigned int n, char str[])
{
	unsigned int	nb;
	int				i;

	nb = n;
	i = 1;
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	str[i] = 0;
	while (--i >= 0)
	{
		str[i] = "0123456789"[nb % 10];
		nb /= 10;
	}
}
