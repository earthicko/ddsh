/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_token.h"
#include "expansion.h"
#include "strutils.h"

static int	_expand_token_assign(t_toks *toks, t_pchararr *arr, int *idx)
{
	int	i;

	i = 0;
	while (i < arr->len)
	{
		(toks->arr)[*idx].content = ft_strdup((arr->data)[i]);
		if (!((toks->arr)[*idx].content))
			return (CODE_ERROR_MALLOC);
		(toks->arr)[*idx].type = TOKENTYPE_WORD;
		i++;
		(*idx)++;
	}
	return (CODE_OK);
}

static int	_expand_token_realloc(t_toks *toks, t_pchararr *arr, int i)
{
	t_token	*new_arr;

	new_arr = malloc(sizeof(t_token) * (toks->n_toks - 1 + arr->len));
	if (!new_arr)
		return (CODE_ERROR_MALLOC);
	ft_memcpy(new_arr, toks->arr,
		sizeof(t_token) * i);
	ft_bzero(new_arr + i,
		sizeof(t_token) * arr->len);
	ft_memcpy(new_arr + i + arr->len, toks->arr + i + 1,
		sizeof(t_token) * (toks->n_toks - 1 - i));
	free(toks->arr);
	toks->arr = new_arr;
	toks->n_toks += (arr->len - 1);
	return (CODE_OK);
}

static int	_expand_token_abort(t_pchararr *arr, int stat)
{
	pchararr_free_all_pchars(arr);
	pchararr_destroy(arr);
	return (stat);
}

static int	_expand_token(t_toks *toks, int *i)
{
	int			stat;
	t_pchararr	*arr;

	if ((toks->arr)[*i].type != TOKENTYPE_WORD)
		return (CODE_OK);
	stat = do_shell_expansion_word_split((toks->arr)[*i].content, &arr);
	if (stat)
		return (stat);
	free((toks->arr)[*i].content);
	(toks->arr)[*i].content = NULL;
	stat = _expand_token_realloc(toks, arr, *i);
	if (stat)
		return (_expand_token_abort(arr, stat));
	stat = _expand_token_assign(toks, arr, i);
	return (_expand_token_abort(arr, stat));
}

int	expand_tokens(t_toks *toks)
{
	int	stat;
	int	i;

	i = 0;
	while (i < toks->n_toks)
	{
		stat = _expand_token(toks, &i);
		if (stat)
			return (stat);
	}
	return (CODE_OK);
}
