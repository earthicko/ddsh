/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msgdef.h"
#include "lexer_internal.h"

static void	_get_word_token(t_toks *toks, int idx, char *str)
{
	const char	*from = str;

	str += _get_word_len(str);
	toks->arr[idx].type = TOKENTYPE_WORD;
	toks->arr[idx].content = ft_substr(from, 0, str - from);
}

static void	_get_op_token(t_toks *toks, int idx, int tok_type)
{
	toks->arr[idx].type = tok_type;
	if (tok_type == TOKENTYPE_PIPE)
		toks->arr[idx].content = ft_strdup("|");
	else if (tok_type == TOKENTYPE_REDIR_IN_HERE)
		toks->arr[idx].content = ft_strdup("<<");
	else if (tok_type == TOKENTYPE_REDIR_OUT_APPEND)
		toks->arr[idx].content = ft_strdup(">>");
	else if (tok_type == TOKENTYPE_REDIR_IN)
		toks->arr[idx].content = ft_strdup("<");
	else if (tok_type == TOKENTYPE_REDIR_OUT)
		toks->arr[idx].content = ft_strdup(">");
}

static int	_free_with_fail(t_toks *toks, int idx)
{
	while (idx >= 0)
	{
		free(toks->arr[idx].content);
		toks->arr[idx].content = 0;
		idx--;
	}
	free(toks->arr);
	toks->arr = 0;
	return (CODE_ERROR_MALLOC);
}

static int	_build_toks_arr(t_toks *toks, char *str)
{
	int	idx;
	int	tok_type;

	idx = 0;
	while (idx < toks->n_toks)
	{
		str += _get_len_space(str);
		tok_type = _get_token_type(str);
		if (tok_type == TOKENTYPE_WORD)
		{
			_get_word_token(toks, idx, str);
			str += _get_word_len(str);
		}
		else if (tok_type == TOKENTYPE_NULL)
			continue ;
		else
		{
			_get_op_token(toks, idx, tok_type);
			str += op_len(str);
		}
		if (!toks->arr[idx].content)
			return (_free_with_fail(toks, idx));
		idx++;
	}
	return (CODE_OK);
}

int	lex_str(char *str, t_toks *toks)
{
	int	stat;

	toks->n_toks = _get_n_toks(str);
	if (toks->n_toks == -1)
	{
		ft_dprintf(2, "%ssyntax error: unclosed quotes\n", MSG_ERROR_PREFIX);
		return (UNCLOSED_QUOTE);
	}
	toks->arr = malloc(sizeof(t_token) * (toks->n_toks + 1));
	if (!toks->arr)
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (CODE_ERROR_MALLOC);
	}
	toks->arr[toks->n_toks].type = TOKENTYPE_NULL;
	toks->arr[toks->n_toks].content = 0;
	stat = _build_toks_arr(toks, str);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
