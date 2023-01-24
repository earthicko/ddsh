/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msgdef.h"
#include "builtin_commands.h"
#include "builtin_internal.h"

static void	_init_get_exec(char **exec_names, t_exec_builtin *exec_ptrs)
{
	exec_names[0] = "cd";
	exec_ptrs[0] = builtin_cd;
	exec_names[1] = "echo";
	exec_ptrs[1] = builtin_echo;
	exec_names[2] = "export";
	exec_ptrs[2] = builtin_export;
	exec_names[3] = "pwd";
	exec_ptrs[3] = builtin_pwd;
	exec_names[4] = "unset";
	exec_ptrs[4] = builtin_unset;
	exec_names[5] = "env";
	exec_ptrs[5] = builtin_env;
	exec_names[6] = "exit";
	exec_ptrs[6] = builtin_exit;
}

int	builtin_exec_by_name(char *name, char **argv)
{
	int				i;
	char			*exec_names[N_BUILTINS];
	t_exec_builtin	execs_ptrs[N_BUILTINS];

	_init_get_exec(exec_names, execs_ptrs);
	i = 0;
	while (i < N_BUILTINS)
	{
		if (is_samestr(exec_names[i], name))
			return (execs_ptrs[i](argv));
		i++;
	}
	ft_dprintf(2, "%scritical: cannot find builtin `%s'\n",
		MSG_ERROR_PREFIX, name);
	return (CODE_ERROR_GENERIC);
}
