/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:32 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:15 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"

static int	_builtin_cd_internal(char *target)
{
	char	*pwd;
	int		stat;

	stat = 0;
	pwd = getcwd(NULL, 0);
	stat |= chdir(target);
	if (stat)
	{
		ft_dprintf(2, "%scd: %s: ", MSG_ERROR_PREFIX, target);
		perror(NULL);
	}
	if (stat == 0 && pwd)
		stat |= envman_setval("OLDPWD", pwd, TRUE);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (pwd)
		stat |= envman_setval("PWD", pwd, TRUE);
	free(pwd);
	if (stat)
		return (1);
	return (CODE_OK);
}

static int	_builtin_cd_to_oldpwd(void)
{
	int		stat;
	char	*target;

	stat = envman_getval("OLDPWD", &target);
	if (stat)
	{
		if (stat == CODE_ERROR_DATA)
			ft_dprintf(2, "%scd: OLDPWD not set\n", MSG_ERROR_PREFIX);
		return (1);
	}
	stat = ft_printf("%s\n", target);
	if (stat < 0)
		return (1);
	stat = _builtin_cd_internal(target);
	free(target);
	return (stat);
}

static int	_builtin_cd_to_home(void)
{
	int		stat;
	char	*target;

	stat = envman_getval("HOME", &target);
	if (stat)
	{
		if (stat == CODE_ERROR_DATA)
			ft_dprintf(2, "%scd: HOME not set\n", MSG_ERROR_PREFIX);
		return (1);
	}
	stat = _builtin_cd_internal(target);
	free(target);
	return (stat);
}

static int	_builtin_cd_to_cwd(void)
{
	int		stat;
	char	*target;

	target = getcwd(NULL, 0);
	if (!target)
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (1);
	}
	stat = _builtin_cd_internal(target);
	free(target);
	return (stat);
}

int	builtin_cd(char **argv)
{
	argv++;
	if (!*argv)
		return (_builtin_cd_to_home());
	else if (!ft_strncmp(*argv, "-", 2))
		return (_builtin_cd_to_oldpwd());
	else if (ft_strlen(*argv) == 0)
		return (_builtin_cd_to_cwd());
	return (_builtin_cd_internal(*argv));
}
