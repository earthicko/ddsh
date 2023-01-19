#include <stddef.h>
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_io_redirect(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_IO_REDIRECT, NULL, 0);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (NULL);
	}
	child = _parse_io_file(p);
	if (child)
		return (_parse_addchild_and_return(p, root, child));
	child = _parse_io_here(p);
	if (child)
		return (_parse_addchild_and_return(p, root, child));
	return (_parse_abort(p, root, NULL));
}
