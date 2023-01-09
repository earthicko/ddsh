#include "t_node.h"
#include "parser_internal.h"
#include <stddef.h>

t_node	*parse_terminal(t_parser *p, int tokentype, int nodetype)
{
	t_node	*root;

	if (parser_is_last_token(p))
		return (NULL);
	if (p->tok_curr->type != tokentype)
		return (NULL);
	root = node_create(nodetype, p->tok_curr->content, 1);
	if (!root)
		return (NULL);
	p->tok_curr++;
	return (root);
}

static int	can_parse_io_op_file(t_parser *p)
{
	if (parser_is_last_token(p))
		return (FALSE);
	if (p->tok_curr->type == TOKENTYPE_REDIR_IN)
		return (TRUE);
	if (p->tok_curr->type == TOKENTYPE_REDIR_OUT)
		return (TRUE);
	if (p->tok_curr->type == TOKENTYPE_REDIR_OUT_APPEND)
		return (TRUE);
	return (FALSE);
}

t_node	*parse_io_op_file(t_parser *p)
{
	t_node	*root;

	if (!can_parse_io_op_file(p))
		return (NULL);
	root = node_create(NODETYPE_IO_OP_FILE, p->tok_curr->content, 1);
	if (!root)
		return (NULL);
	p->tok_curr++;
	return (root);
}
