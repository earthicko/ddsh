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
		return (parse_addchild_and_return(p, root, child));
	child = parse_io_redirect(p);
	if (child)
		return (parse_addchild_and_return(p, root, child));
	return (parse_abort(p, root, NULL));
}
