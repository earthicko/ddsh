#include <stdlib.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

int	parser_is_last_token(t_parser *parser)
{
	if (parser->tok_curr == parser->tok_last)
		return (TRUE);
	return (FALSE);
}

t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_parser	parser;

	parser.tok_start = tokenarr;
	parser.tok_curr = tokenarr;
	parser.tok_last = tokenarr + n_tokens;
	parser.n_tokens = n_tokens;
	return (parse_pipe_sequence(&parser));
}
