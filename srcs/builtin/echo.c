/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:18 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	_has_only_ch(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ch)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	_is_valid_option(char *arg)
{
	if (!arg)
		return (FALSE);
	if (ft_strncmp(arg, "-n", 2) == 0 && _has_only_ch(arg + 2, 'n'))
		return (TRUE);
	return (FALSE);
}

static int	_builtin_flag_n_on(char *first_arg)
{
	if (!first_arg)
		return (FALSE);
	if (_is_valid_option(first_arg))
		return (TRUE);
	return (FALSE);
}

int	builtin_echo(char **argv)
{
	int	flag_n;

	argv++;
	flag_n = _builtin_flag_n_on(*argv);
	while (flag_n && _is_valid_option(*argv))
		argv++;
	while (*argv)
	{
		if (ft_printf("%s", *argv) < 0)
			return (1);
		argv++;
		if (*argv)
		{
			if (ft_printf("%c", ' ') < 0)
				return (1);
		}
	}
	if (!flag_n)
	{
		if (ft_printf("%c", '\n') < 0)
			return (1);
	}
	return (0);
}
