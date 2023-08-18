/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:26 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"

int	_exit_compose(t_pchararr *strarr, char *word)
{
	int	stat;

	stat = pchararr_append(strarr, word);
	if (stat)
	{
		free(word);
		return (stat);
	}
	return (CODE_OK);
}
