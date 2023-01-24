/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	builtin_pwd(char **argv)
{
	char	*pwd;
	int		stat;

	(void)argv;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	stat = ft_printf("%s\n", pwd);
	free(pwd);
	if (stat < 0)
		return (1);
	return (0);
}
