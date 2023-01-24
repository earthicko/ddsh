/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "t_token.h"

void	token_destroy(t_toks *toks)
{
	int	i;

	if (toks->arr)
	{
		i = 0;
		while (i < toks->n_toks)
		{
			free(toks->arr[i].content);
			i++;
		}
		free(toks->arr);
		toks->arr = NULL;
	}
	toks->n_toks = 0;
}
