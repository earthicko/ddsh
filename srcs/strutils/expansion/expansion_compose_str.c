/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_compose_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "strutils.h"
#include "expansion_internal.h"

int	_compose_str(char *str, int *pos, t_pchararr *strarr)
{
	int		start;
	char	*word;

	start = *pos;
	while (str[*pos] != '\0'
		&& str[*pos] != '\''
		&& str[*pos] != '\"'
		&& str[*pos] != '$')
		(*pos)++;
	word = ft_substr(str, start, *pos - start);
	if (!word)
		return (CODE_ERROR_MALLOC);
	return (_exit_compose(strarr, word));
}
