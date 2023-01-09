#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>
#include "libft_def.h"

t_node	*parse_cmd_element(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_CMD_ELEMENT, NULL, 0);
	if (!root)
		return (NULL);
	child = parse_terminal(p, TOKENTYPE_WORD, NODETYPE_CMD_WORD);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(p, root, child));
		return (root);
	}
	child = parse_io_redirect(p);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(p, root, child));
		return (root);
	}
	return (parse_abort(p, root, NULL));
}
