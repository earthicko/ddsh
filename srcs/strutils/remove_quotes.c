/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:21 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:45:22 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	_count_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			i++;
		str++;
	}
	return (i);
}

int	remove_quotes(char **buf)
{
	char	*backup;
	int		i;
	int		j;

	backup = malloc(sizeof(char) * (ft_strlen(*buf) - _count_quotes(*buf) + 1));
	if (!backup)
		return (CODE_ERROR_MALLOC);
	i = 0;
	j = 0;
	while ((*buf)[i])
	{
		if (!((*buf)[i] == '\'' || (*buf)[i] == '\"'))
		{
			backup[j] = (*buf)[i];
			j++;
		}
		i++;
	}
	backup[j] = '\0';
	free(*buf);
	*buf = backup;
	return (CODE_OK);
}
