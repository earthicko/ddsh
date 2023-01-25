/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_declare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"
#include "msgdef.h"
#include "envmanager.h"

static int	_exit_declare_var(int stat, char *word)
{
	if (stat == CODE_ERROR_DATA)
		ft_dprintf(2, "%sdeclare: `%s': not a valid identifier\n",
			MSG_ERROR_PREFIX, word);
	else if (stat == CODE_ERROR_MALLOC)
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
	if (stat)
		return (1);
	return (0);
}

static int	declare_var(char *word)
{
	char	*name;
	char	*val;
	int		stat;

	if (!ft_strchr(word, '=') && !is_valid_name(word))
		return (_exit_declare_var(CODE_ERROR_DATA, word));
	if (!ft_strchr(word, '='))
		return (_exit_declare_var(envman_setval(word, NULL, FALSE), word));
	stat = envman_split_envstr(word, &name, &val);
	if (stat)
		return (_exit_declare_var(stat, word));
	stat = envman_setval(name, val, FALSE);
	free(name);
	free(val);
	return (_exit_declare_var(stat, word));
}

int	builtin_declare(char **argv)
{
	int	stat;

	argv++;
	if (!*argv)
		return (envman_declare());
	stat = 0;
	while (*argv)
	{
		if (declare_var(*argv))
			stat = 1;
		argv++;
	}
	return (stat);
}
