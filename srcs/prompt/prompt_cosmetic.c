/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cosmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:43:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:43:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "prompt_string.h"

void	prompt_print_banner(void)
{
	ft_printf("%s%s%s\n", _B_00_0, _B_00_1, _B_00_2);
	ft_printf("%s%s%s\n", _B_01_0, _B_01_1, _B_01_2);
	ft_printf("%s%s%s\n", _B_02_0, _B_02_1, _B_02_2);
	ft_printf("%s%s%s\n", _B_03_0, _B_03_1, _B_03_2);
	ft_printf("%s%s%s\n", _B_04_0, _B_04_1, _B_04_2);
	ft_printf("%s%s%s\n", _B_05_0, _B_05_1, _B_05_2);
	ft_printf("%s%s%s\n", _B_06_0, _B_06_1, _B_06_2);
	ft_printf("%s%s%s\n", _B_07_0, _B_07_1, _B_07_2);
	ft_printf("%s%s%s\n", _B_08_0, _B_08_1, _B_08_2);
	ft_printf("%s%s%s\n", _B_09_0, _B_09_1, _B_09_2);
	ft_printf("%s%s%s%s%s %s\n\n", _B_10_0, _B_10_1, _B_10_2,
		_B_CREDIT_0, _B_CREDIT_1, _B_VER);
}
