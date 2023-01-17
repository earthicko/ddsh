#include <stddef.h>
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_io_file(t_parser *p)
{
	t_node	*root;

	root = node_create(NODETYPE_IO_FILE, NULL, 0);
	if (!root)
		return (_parse_abort(p, NULL, NULL));
	if (_parse_terminal_and_addchild(p, NODETYPE_IO_OP_FILE, root))
		return (NULL);
	if (_parse_terminal_and_addchild(p, NODETYPE_FILENAME, root))
		return (NULL);
	return (root);
}
