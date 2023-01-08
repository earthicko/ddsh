#include "t_node.h"
#include "t_token.h"
#include "parser.h"
#include <stddef.h>

t_node	*abort_parse(t_parser *parser, t_node *root, t_node *child)
{
	int	rewind_counter;

	rewind_counter = 0;
	if (root)
	{
		rewind_counter += getntokens_node(root);
		destroy_node(root);
	}
	if (child)
	{
		rewind_counter += getntokens_node(child);
		destroy_node(child);
	}
	parser->tok_curr -= rewind_counter;
	return (NULL);
}
