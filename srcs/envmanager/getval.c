/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_getval.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

static int	_envman_getexitstat(char **buf)
{
	char	*backup;

	backup = ft_itoa(exit_stat_manager(-1));
	if (!backup)
		return (CODE_ERROR_MALLOC);
	*buf = backup;
	return (CODE_OK);
}

int	_envman_getval(t_list *envlist, char **buf, char *name)
{
	t_enventry	*entry;
	char		*backup;

	if (_envman_isspecialval(name))
		return (_envman_get_specialval(name, buf));
	if (_envman_isescapechar(name))
		return (_envman_getescape(name, buf));
	if (ft_strncmp(name, "?", 2) == 0)
		return (_envman_getexitstat(buf));
	entry = _enventry_getentry(envlist, name);
	if (!entry)
		return (CODE_ERROR_DATA);
	if (entry->val)
		backup = ft_strdup(entry->val);
	else
		backup = ft_strdup("");
	if (!backup)
		return (CODE_ERROR_MALLOC);
	*buf = backup;
	return (CODE_OK);
}

int	envman_getval(char *name, char **buf)
{
	int				stat;
	t_envmaninfo	info;

	info.name = name;
	info.buf = buf;
	stat = _envmanager(ENVMANMODE_GETVAL, &info);
	if (stat && stat != CODE_ERROR_DATA)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
