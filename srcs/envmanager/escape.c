/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_specialval_escape.c                     :+:      :+:    :+:   */
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

int	_envman_isescapechar(char *name)
{
	if (ft_strncmp(name, "ESC", 3) == 0)
		return (TRUE);
	return (FALSE);
}

static void	_init_envman_set_escape_idx_0(t_envman_getter *getters)
{
	getters[0] = _envman_escape_reset;
	getters[1] = _envman_escape_red;
	getters[2] = _envman_escape_green;
	getters[3] = _envman_escape_yellow;
	getters[4] = _envman_escape_blue;
	getters[5] = _envman_escape_magenta;
	getters[6] = _envman_escape_cyan;
	getters[7] = _envman_escape_white;
	getters[8] = _envman_escape_bblack;
	getters[9] = _envman_escape_bred;
	getters[10] = _envman_escape_bgreen;
	getters[11] = _envman_escape_byellow;
	getters[12] = _envman_escape_bblue;
	getters[13] = _envman_escape_bmagenta;
	getters[14] = _envman_escape_bcyan;
	getters[15] = _envman_escape_bwhite;
	getters[16] = _envman_escape_newline;
}

static void	_init_envman_set_escape_idx_1(char **names)
{
	names[0] = "ESC_RESET";
	names[1] = "ESC_RED";
	names[2] = "ESC_GREEN";
	names[3] = "ESC_YELLOW";
	names[4] = "ESC_BLUE";
	names[5] = "ESC_MAGENTA";
	names[6] = "ESC_CYAN";
	names[7] = "ESC_WHITE";
	names[8] = "ESC_BBLACK";
	names[9] = "ESC_BRED";
	names[10] = "ESC_BGREEN";
	names[11] = "ESC_BYELLOW";
	names[12] = "ESC_BBLUE";
	names[13] = "ESC_BMAGENTA";
	names[14] = "ESC_BCYAN";
	names[15] = "ESC_BWHITE";
	names[16] = "ESC_NEWLINE";
}

int	_envman_get_escape_idx(char *name)
{
	int				i;
	char			*names[ENVMAN_N_ESCAPE];
	t_envman_getter	getters[ENVMAN_N_ESCAPE];

	_init_envman_set_escape_idx_0(getters);
	_init_envman_set_escape_idx_1(names);
	i = 0;
	while (i < ENVMAN_N_ESCAPE)
	{
		if (is_samestr(names[i], name))
			return (i);
		i++;
	}
	return (-1);
}

int	_envman_getescape(char *name, char **buf)
{
	int				i;
	char			*names[ENVMAN_N_ESCAPE];
	t_envman_getter	getters[ENVMAN_N_ESCAPE];
	char			*temp;

	_init_envman_set_escape_idx_0(getters);
	_init_envman_set_escape_idx_1(names);
	i = _envman_get_escape_idx(name);
	if (i >= ENVMAN_N_ESCAPE || i < 0)
	{
		temp = ft_strdup("");
		if (!temp)
			return (CODE_ERROR_MALLOC);
		*buf = temp;
		return (CODE_OK);
	}
	temp = getters[i]();
	if (!temp)
		return (CODE_ERROR_GENERIC);
	*buf = temp;
	return (CODE_OK);
}
