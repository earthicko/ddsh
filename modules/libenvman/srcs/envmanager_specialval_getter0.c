/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_get_specialval0.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "msgdef.h"
#include "libft.h"
#include "envmanager_internal.h"

char	*_envman_get_time(void)
{
	char		buf[BUFFER_SIZE];
	char		*format;
	int			stat;
	time_t		t;
	struct tm	*_tm;

	stat = envman_getval("DDSH_TIME_FORMAT", &format);
	if (stat)
	{
		ft_dprintf(2, "%sDDSH_TIME_FORMAT not set\n", MSG_ERROR_PREFIX);
		return (NULL);
	}
	t = time(NULL);
	_tm = localtime(&t);
	if (strftime(buf, BUFFER_SIZE, format, _tm) == 0)
	{
		free(format);
		ft_dprintf(2, "%sBUFFER_SIZE not sufficient\n", MSG_ERROR_PREFIX);
		return (NULL);
	}
	free(format);
	return (ft_strdup(buf));
}

char	*_envman_get_pwd(void)
{
	return (getcwd(NULL, 0));
}

char	*_envman_get_hostname(void)
{
	char	buf[BUFFER_SIZE];

	if (gethostname(buf, BUFFER_SIZE))
	{
		perror(MSG_ERROR_PREFIX);
		return (NULL);
	}
	return (ft_substr(buf, 0, ft_strchr(buf, '.') - buf));
}
