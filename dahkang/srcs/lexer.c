#include "../libft/includes/libft.h"
#include "../includes/lexer.h"

#include <stdio.h>

//토큰화 로직은 토큰 개수세는 로직과 달리 바꾸는게 나을듯.
t_toks	*lexer(char *str)
{
	t_toks	*toks;	
	int		state;
	char	quote;
	int		idx;
	char	*from;

	if (!str)
		return (0);
	toks = init_toks(str);
	if (toks->n_toks == -1)
		return (toks);
	quote = 0;
	state = SEP;
	idx = 0;
	while (*str)
	{
		if (!quote && is_space(*str))
		{
			if (state == NOTSEP)
			{
				toks->arr[idx].content = ft_substr(from, 0, str - from - 1);
				toks->arr[idx].type = TOKENTYPE_WORD;
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
			idx++;
			state = SEP;
		}
		if (skip_letter(&str))
		{
			if (state == SEP)
				from = str;
			state = NOTSEP;
		}
	}
	return (toks);
}
