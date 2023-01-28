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

#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "strutils.h"
#include "msgdef.h"
#include "prompt_banner.h"

void	prompt_print_banner(void)
{
	ft_printf("%s%s%s%s\n", _B_00_0, _B_00_1, _B_00_2, _B_00_3);
	ft_printf("%s%s%s%s\n", _B_01_0, _B_01_1, _B_01_2, _B_01_3);
	ft_printf("%s%s%s%s\n", _B_02_0, _B_02_1, _B_02_2, _B_02_3);
	ft_printf("%s%s%s%s\n", _B_03_0, _B_03_1, _B_03_2, _B_03_3);
	ft_printf("%s%s%s%s\n", _B_04_0, _B_04_1, _B_04_2, _B_04_3);
	ft_printf("%s%s%s%s\n", _B_05_0, _B_05_1, _B_05_2, _B_05_3);
	ft_printf("%s%s%s%s %s\n", _B_06_0, _B_06_1, _B_06_2, _B_06_3, _B_CREDIT_0);
	ft_printf("%s%s%s%s %s\n", _B_07_0, _B_07_1, _B_07_2, _B_07_3, _B_CREDIT_1);
	ft_printf("%s%s%s%s %s\n", _B_08_0, _B_08_1, _B_08_2, _B_08_3, _B_CREDIT_2);
	ft_printf("%s%s%s%s %s\n", _B_09_0, _B_09_1, _B_09_2, _B_09_3, _B_CREDIT_3);
	ft_printf("%s%s%s%s %s\n\n", _B_10_0, _B_10_1, _B_10_2, _B_10_3, _B_VER);
}

char	*prompt_get_prompt_prefix(void)
{
	char	*buf;
	int		stat;

	if (envman_getval("DDSH_THEME", &buf))
		return (ft_strdup(MSG_SHELL_PROMPT));
	stat = do_shell_expansion(&buf);
	if (stat)
	{
		ft_print_error(MSG_ERROR_PREFIX, stat);
		free(buf);
		return (ft_strdup(MSG_SHELL_PROMPT));
	}
	return (buf);
}
