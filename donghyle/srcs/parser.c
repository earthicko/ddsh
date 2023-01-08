#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stdlib.h>

t_parser	*create_parser(t_token *tokenarr, int n_tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->tok_start = tokenarr;
	parser->tok_curr = tokenarr;
	parser->tok_last = tokenarr + n_tokens;
	parser->n_tokens = n_tokens;
	parser->rewind_counter = 0;
	return (parser);
}

int	parser_is_last_token(t_parser *parser)
{
	if (parser->tok_curr == parser->tok_last)
		return (1);
	return (0);
}

void	parser_increment_token(t_parser *parser, int n)
{
	parser->tok_curr += n;
	parser->rewind_counter += n;
}

t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_parser	*parser;
	t_node		*root;

	parser = create_parser(tokenarr, n_tokens);
	if (!parser)
		return (NULL);
	root = parse_pipe_sequence(parser);
	return (root);
}
