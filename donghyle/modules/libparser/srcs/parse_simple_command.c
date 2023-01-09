#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>
#include "libft_def.h"

t_node	*parse_simple_command(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(p))
		return (NULL);
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
