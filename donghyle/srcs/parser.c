#include "t_node.h"
#include "t_token.h"
#include <stdlib.h>

t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_token	*token_p;
	t_token	*last_token;
	t_node	*root;

	token_p = tokenarr;
	last_token = tokenarr + n_tokens;
	root = parse_pipe_sequence(&token_p, last_token);
	return (root);
}
