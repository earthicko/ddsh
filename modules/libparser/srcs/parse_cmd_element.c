#include <stddef.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_cmd_element(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = _node_create(NODETYPE_CMD_ELEMENT, NULL, 0);
	if (!root)
		return (NULL);
	child = _parse_terminal(p, NODETYPE_CMD_WORD);
	if (child)
		return (_parse_addchild_and_return(p, root, child));
	child = _parse_io_redirect(p);
	if (child)
		return (_parse_addchild_and_return(p, root, child));
	return (_parse_abort(p, root, NULL));
}
