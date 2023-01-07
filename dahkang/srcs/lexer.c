#include "../libft/includes/libft.h"
#include "../includes/lexer.h"

static int	get_n_toks(char *str)
{
	int	n_toks;

	while (*str)
	{
		skip_space(str);
		if (*str && *str == '\'')
	}

	return (n_toks);
}

static	t_toks	*init_toks(char *str)
{
	t_toks	*toks;

	toks = (t_toks *)malloc(sizeof(t_toks));
	if (!toks)
		return (0);
	toks->n_toks = get_n_toks(str);
	toks->arr = (t_token *)malloc(sizeof(t_token) * (toks->n_toks + 1));
	if (!toks->arr)
		return (0);
	return (toks);
}

//인풋이 그냥 엔터일 때, 동적할당 실패하는 경우를 나누어야 하나?
t_toks	*lexer(char *str)
{
	t_toks	*toks;	
	int		i;
	char	*start;

	if (!str)
		return (0);
	toks = init_toks(str);
	while (*str)
	{
		if (skip_space(str))
			return (0);
		if (*str == '\'' || *str == '"')
		{
			start = str;
			while (*str && *str == '\'')
				str++;
		}
	}
}
