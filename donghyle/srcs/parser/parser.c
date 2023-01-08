#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stdlib.h>

t_parser	*parser_create(t_token *tokenarr, int n_tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->tok_start = tokenarr;
	parser->tok_curr = tokenarr;
	parser->tok_last = tokenarr + n_tokens;
	parser->n_tokens = n_tokens;
	return (parser);
}

int	parser_is_last_token(t_parser *parser)
{
	if (parser->tok_curr == parser->tok_last)
		return (1);
	return (0);
}

t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_parser	*parser;
	t_node		*root;

	parser = parser_create(tokenarr, n_tokens);
	if (!parser)
		return (NULL);
	root = parse_pipe_sequence(parser);
	free(parser);
	return (root);
}
