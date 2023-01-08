#include "t_node.h"
#include "t_token.h"
#include "parser.h"
#include <stddef.h>

t_node	*parse_abort(t_parser *parser, t_node *root, t_node *child)
{
	int	rewind_counter;

	rewind_counter = 0;
	if (root)
	{
		rewind_counter += node_getntokens(root);
		node_destroy(root);
	}
	if (child)
	{
		rewind_counter += node_getntokens(child);
		node_destroy(child);
	}
	parser->tok_curr -= rewind_counter;
	return (NULL);
}
