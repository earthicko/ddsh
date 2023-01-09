#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include "libft_def.h"
#include <stddef.h>

static int	can_parse_io_op_file(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (FALSE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_IN)
		return (TRUE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT)
		return (TRUE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT_APPEND)
		return (TRUE);
	return (FALSE);
}

t_node	*parse_io_op_file(t_parser *parser)
{
	t_node	*root;

	if (!can_parse_io_op_file(parser))
		return (NULL);
	root = node_create(NODETYPE_IO_OP_FILE, parser->tok_curr->content, 1);
	if (!root)
		return (NULL);
	parser->tok_curr++;
	return (root);
}

t_node	*parse_io_file(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_IO_FILE, NULL, 0);
	if (!root)
		return (parse_abort(parser, NULL, NULL));
	child = parse_io_op_file(parser);
	if (!child)
		return (parse_abort(parser, root, NULL));
	if (node_addchild(root, child))
		return (parse_abort(parser, root, child));
	child = parse_filename(parser);
	if (!child)
		return (parse_abort(parser, root, NULL));
	if (node_addchild(root, child))
		return (parse_abort(parser, root, child));
	return (root);
}

t_node	*parse_io_redirect(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_IO_REDIRECT, NULL, 0);
	if (!root)
		return (NULL);
	child = parse_io_file(parser);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		return (root);
	}
	child = parse_io_here(parser);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		return (root);
	}
	return (parse_abort(parser, root, NULL));
}
