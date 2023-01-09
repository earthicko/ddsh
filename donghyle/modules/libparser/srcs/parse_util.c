#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include "libft_def.h"
#include <stddef.h>

t_node	*parse_addchild_and_return(t_parser *p, t_node *root, t_node *child)
{
	if (node_addchild(root, child))
		return (parse_abort(p, root, child));
	return (root);
}

t_node	*parse_abort(t_parser *p, t_node *root, t_node *child)
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
	p->tok_curr -= rewind_counter;
	return (NULL);
}
