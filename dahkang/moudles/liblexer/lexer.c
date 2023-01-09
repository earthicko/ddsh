#include "../../libft/includes/libft.h"
#include "../../includes/lexer.h"

#include <stdio.h>

//동적할당 실패에 대한 에러처리 코드 추가할 것

static void	get_word_token(t_toks *toks, int idx, char *str)
{
	const char	*from = str;

	str += get_word_len(str);
	toks->arr[idx].type = TOKENTYPE_WORD;
	toks->arr[idx].content = ft_substr(from, 0, str - from);
}

static void	get_op_token(t_toks *toks, int idx, int tok_type)
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

t_toks *free_toks(t_toks *toks, int idx)	
{
	while (idx >= 0)
	{
		free(toks->arr[idx].content);
		toks->arr[idx].content = 0;
		idx--;
	}
	free(toks->arr);
	toks->arr = 0;
	free(toks);
	return (0);
}

t_toks	*build_toks_arr(t_toks *toks, char *str)
{
	int	idx;
	int	tok_type;

	idx = -1;
	while (++idx < toks->n_toks)
	{
		str += space_len(str);
		tok_type = get_token_type(str);
		if (tok_type == TOKENTYPE_WORD)
		{
			get_word_token(toks, idx, str);
			str += get_word_len(str);
		}
		else if (tok_type == TOKENTYPE_NULL)
			continue ;
		else
		{
			get_op_token(toks, idx, tok_type);
			str += op_len(str);
		}
		//if (idx == 5)
		if (!toks->arr[idx].content)
			return (free_toks(toks, idx));
	}
	return (toks);
}

//malloc실패에 대한 로직은 별도로 작성
t_toks	*lexer(char *str)
{
	t_toks	*toks;	

	if (!str)
		return (0);
	toks = init_toks(str);
	if (toks->n_toks == -1)
		return (toks);
	return (build_toks_arr(toks, str));
}
	/*
	idx = -1;
	while (++idx < toks->n_toks)
	{
		str += space_len(str);
		tok_type = get_token_type(str);
		if (tok_type == TOKENTYPE_WORD)
		{
			get_word_token(toks, idx, str);
			str += get_word_len(str);
		}
		else if (tok_type == TOKENTYPE_NULL)
			continue ;
		else
		{
			get_op_token(toks, idx, tok_type);
			str += op_len(str);
		}
	}
	return (toks);
	*/

	/*
	while (*str)
	{
		if (!quote && is_space(*str))
		{
			if (state == NOTSEP && from != 0)
			{
				toks->arr[idx].type = TOKENTYPE_WORD;
				toks->arr[idx++].content = ft_substr(from, 0, str - from - 1);
				from = 0;
			}
			skip_space(&str);
			state = SEP;
		}
		if (*str && *str == '\'' || *str == '"')
		{
			if (state == SEP)
				from = str;
			if (quote == 0)
				quote = *str;
			skip_inquote(&str, quote);
			quote = 0;
			str++;
			state = NOTSEP;
		}
		if (!quote && *str && is_metachar(*str))
		{
			if (state == NOTSEP && from != 0)
			{
				toks->arr[idx].type = TOKENTYPE_WORD;
				toks->arr[idx++].content = ft_substr(from, 0, str - from - 1);
				from = 0;
			}
			toks->arr[idx].type = get_token_type(str);
			skip_metachar(&str);
			state = SEP;
		}
		if (skip_letter(&str))
		{
			if (state == SEP)
				from = str;
			state = NOTSEP;
		}
	}
*/
