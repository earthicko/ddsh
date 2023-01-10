#include <stddef.h>
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*parse_io_here(t_parser *p)
{
	t_node	*root;

	root = node_create(NODETYPE_IO_HERE, NULL, 0);
	if (!root)
		return (parse_abort(p, NULL, NULL));
	if (parse_terminal_and_addchild(p, NODETYPE_IO_OP_HERE, root))
		return (NULL);
	if (parse_terminal_and_addchild(p, NODETYPE_HERE_END, root))
		return (NULL);
	return (root);
}
