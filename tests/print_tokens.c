#include "t_token.h"
#include <stdio.h>

void	print_tokens(t_token *p_token, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		printf("%s ", p_token[i].content);
		i++;
	}
	printf("\n");
}
