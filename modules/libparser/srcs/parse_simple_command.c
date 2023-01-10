#include <stddef.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*parse_simple_command(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_SIMPLE_COMMAND, NULL, 0);
	if (!root)
		return (NULL);
	while (TRUE)
	{
		child = parse_cmd_element(p);
		if (!child)
		{
			if (node_getntokens(root))
				return (root);
			return (parse_abort(p, root, NULL));
		}
		if (node_addchild(root, child))
			return (parse_abort(p, root, child));
	}
}
