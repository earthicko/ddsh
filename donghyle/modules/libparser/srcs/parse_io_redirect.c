#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>

t_node	*parse_io_redirect(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_IO_REDIRECT, NULL, 0);
	if (!root)
		return (NULL);
	child = parse_io_file(p);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(p, root, child));
		return (root);
	}
	child = parse_io_here(p);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(p, root, child));
		return (root);
	}
	return (parse_abort(p, root, NULL));
}
