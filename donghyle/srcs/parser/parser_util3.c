#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>

#include "libft.h"

t_node	*parse_cmd_element(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type == TOKENTYPE_WORD)
	{
		root = node_create(NODETYPE_CMD_ELEMENT, parser->tok_curr->content, 1);
		if (!root)
			return (parse_abort(parser, NULL, NULL));
		parser_increment_token(parser, 1);
		return (root);
	}
	root = node_create(NODETYPE_CMD_ELEMENT, "", 0);
	if (!root)
		return (parse_abort(parser, NULL, NULL));
	child = parse_io_redirect(parser);
	if (!child)
		return (parse_abort(parser, root, NULL));
	if (node_addchild(root, child))
		return (parse_abort(parser, root, child));
	return (root);
}

t_node	*parse_simple_command(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	root = node_create(NODETYPE_SIMPLE_COMMAND, "", 0);
	if (!root)
		return (NULL);
	while (1)
	{
		child = parse_cmd_element(parser);
		if (!child)
			return (root);
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
	}
}

t_node	*parse_pipe_sequence(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	root = node_create(NODETYPE_PIPE_SEQUENCE, "|", 0);
	if (!root)
		return (NULL);
	while (1)
	{
		child = parse_simple_command(parser);
		if (!child)
			return (parse_abort(parser, root, NULL));
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		if (parser_is_last_token(parser))
			return (root);
		if (parser->tok_curr->type != TOKENTYPE_PIPE)
			return (node_destroy(root));
		parser_increment_token(parser, 1);
		root->n_tokens++;
	}
	return (node_destroy(root));
}
