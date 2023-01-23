/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pchararr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:21 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:45:24 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "strutils.h"

t_pchararr	*pchararr_create(void)
{
	t_pchararr	*pchararr;

	pchararr = malloc(sizeof(t_pchararr));
	if (!pchararr)
		return (NULL);
	pchararr->data = malloc(sizeof(char *) * PCHARARR_INITIAL_CAP);
	if (!(pchararr->data))
	{
		free(pchararr);
		return (NULL);
	}
	pchararr->len = 0;
	pchararr->cap = PCHARARR_INITIAL_CAP;
	return (pchararr);
}

t_pchararr	*pchararr_destroy(t_pchararr *pchararr)
{
	free(pchararr->data);
	free(pchararr);
	return (NULL);
}

int	pchararr_expand(t_pchararr *pchararr)
{
	char	**new_data;

	new_data = malloc(sizeof(char *) * pchararr->cap * 2);
	if (!new_data)
		return (CODE_ERROR_MALLOC);
	ft_memcpy(new_data, pchararr->data, sizeof(char *) * pchararr->len);
	free(pchararr->data);
	pchararr->data = new_data;
	pchararr->cap = pchararr->cap * 2;
	return (CODE_OK);
}

int	pchararr_append(t_pchararr *pchararr, char *data)
{
	if (pchararr->len == pchararr->cap)
	{
		if (pchararr_expand(pchararr))
			return (CODE_ERROR_MALLOC);
	}
	(pchararr->data)[pchararr->len] = data;
	(pchararr->len)++;
	return (CODE_OK);
}
