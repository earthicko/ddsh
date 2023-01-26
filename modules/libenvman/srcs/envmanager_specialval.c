/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_specialval.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envmanager_internal.h"

typedef char	*(*t_envman_getter)(void);

static void	_init_envman_set_specialval_idx(
			char **names, t_envman_getter *getters)
{
	names[0] = "DDSH_TIME";
	getters[0] = _envman_get_time;
	names[1] = "DDSH_PWD";
	getters[1] = _envman_get_pwd;
	names[2] = "DDSH_HOSTNAME";
	getters[2] = _envman_get_hostname;
}

static int	_envman_get_specialval_idx(char *name)
{
	int				i;
	char			*names[ENVMAN_N_SPECIALVAL];
	t_envman_getter	getters[ENVMAN_N_SPECIALVAL];

	_init_envman_set_specialval_idx(names, getters);
	i = 0;
	while (i < ENVMAN_N_SPECIALVAL)
	{
		if (is_samestr(names[i], name))
			return (i);
		i++;
	}
	return (-1);
}

int	_envman_isspecialval(char *name)
{
	if (_envman_get_specialval_idx(name) >= 0)
		return (TRUE);
	return (FALSE);
}

int	_envman_get_specialval(char *name, char **buf)
{
	int				i;
	char			*names[ENVMAN_N_SPECIALVAL];
	t_envman_getter	getters[ENVMAN_N_SPECIALVAL];
	char			*temp;

	_init_envman_set_specialval_idx(names, getters);
	i = 0;
	while (i < ENVMAN_N_SPECIALVAL)
	{
		if (is_samestr(names[i], name))
		{
			temp = getters[i]();
			if (!temp)
				return (CODE_ERROR_GENERIC);
			*buf = temp;
			return (CODE_OK);
		}
		i++;
	}
	return (CODE_ERROR_SCOPE);
}
