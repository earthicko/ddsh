#include <stddef.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_pipe_sequence(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_PIPE_SEQUENCE, NULL, 0);
	if (!root)
		return (NULL);
	while (TRUE)
	{
		child = _parse_simple_command(p);
		if (!child)
			return (_parse_abort(p, root, NULL));
		if (node_addchild(root, child))
			return (_parse_abort(p, root, child));
		if (_parser_is_last_token(p))
			return (root);
		if (p->tok_curr->type != TOKENTYPE_PIPE)
			return (_parse_abort(p, root, NULL));
		p->tok_curr++;
		root->n_tokens++;
	}
}
