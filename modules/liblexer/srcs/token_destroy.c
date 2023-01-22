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

#include "lexer_internal.h"

void	token_destroy(t_toks *toks)
{
	int	i;

	i = -1;
	while (++i < toks->n_toks)
	{
		free(toks->arr[i].content);
		toks->arr[i].content = 0;
	}
	toks->n_toks = 0;
	free(toks->arr);
	toks->arr = 0;
}
