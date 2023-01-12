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
