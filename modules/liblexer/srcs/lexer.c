#include "libft.h"
#include "lexer_internal.h"
#include "libft_def.h"

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

static int	free_with_fail(t_toks *toks, int idx)
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

static int	build_toks_arr(t_toks *toks, char *str)
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
		if (!toks->arr[idx].content)
			return (free_with_fail(toks, idx));
	}
	return (CODE_OK);
}

int	lexer(char *str, t_toks *toks)
{
	if (!str)
		return (CODE_ERROR_DATA);
	toks->n_toks = get_n_toks(str);
	if (toks->n_toks == -1)
		return (UNCLOSED_QUOTE);
	toks->arr = (t_token *)malloc(sizeof(t_token) * (toks->n_toks + 1));
	if (!toks->arr)
		return (CODE_ERROR_MALLOC);
	toks->arr[toks->n_toks].type = TOKENTYPE_NULL;
	toks->arr[toks->n_toks].content = 0;
	return (build_toks_arr(toks, str));
}
