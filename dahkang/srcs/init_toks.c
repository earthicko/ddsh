#include "../libft/includes/libft.h"
#include "../includes/lexer.h"

#include <stdio.h>

//test이후에 static 선언 할 것
int	get_n_toks(char *str)
{
	int		n_toks;
	char	quote;
	int		state;

	printf("str: %s\n", str);
	n_toks = 0;
	quote = 0;
	state = SEP;
	//공백이나 메타캐릭터를 기준으로 토큰을 쪼갬
	while (*str)
	{
		if (skip_space(&str))
			state = SEP;
		if (*str && *str == '\'' || *str == '"')
		{
			quote = *str++;
			skip_inquote(&str, quote);
			if (*str != quote)
				return (-1);
			quote = 0;
			str++;
			if (state == SEP)
				n_toks++;
			state = NOTSEP;
		}
		if (*str && skip_metachar(&str))
		{
			n_toks++;
			state = SEP;
		}
		if (skip_letter(&str))
		{
			if (state == SEP)
				n_toks++;
			state = NOTSEP;
		}
	}
	return (n_toks);
}

t_toks	*init_toks(char *str)
{
	t_toks	*toks;

	toks = (t_toks *)malloc(sizeof(t_toks));
	if (!toks)
		return (0);
	ft_memset(toks, 0, sizeof(t_toks));
	toks->n_toks = get_n_toks(str);
	//Unclosed quote인 경우 토큰 개수 -1 리턴
	if (toks->n_toks == -1)
		return (toks);
	toks->arr = (t_token *)malloc(sizeof(t_token) * (toks->n_toks + 1));
	if (!toks->arr)
		return (0);
	return (toks);
}
