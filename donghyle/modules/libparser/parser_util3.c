#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>
#include "libft_def.h"

t_node	*parse_cmd_word(t_parser *parser)
{
	t_node	*root;

	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type != TOKENTYPE_WORD)
		return (NULL);
	root = node_create(NODETYPE_CMD_WORD, parser->tok_curr->content, 1);
	if (!root)
		return (NULL);
	parser->tok_curr++;
	return (root);
}

t_node	*parse_cmd_element(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_CMD_ELEMENT, NULL, 0);
	if (!root)
		return (NULL);
	child = parse_cmd_word(parser);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		return (root);
	}
	child = parse_io_redirect(parser);
	if (child)
	{
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		return (root);
	}
	return (parse_abort(parser, root, NULL));
}

t_node	*parse_simple_command(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	root = node_create(NODETYPE_SIMPLE_COMMAND, NULL, 0);
	if (!root)
		return (NULL);
	while (TRUE)
	{
		child = parse_cmd_element(parser);
		if (!child)
		{
			if (node_getntokens(root))
				return (root);
			return (parse_abort(parser, root, NULL));
		}
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
	}
}

static int	can_parse_pipe_sequence(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (FALSE);
	if (parser->tok_curr->type == TOKENTYPE_PIPE)
		return (FALSE);
	return (TRUE);
}

t_node	*parse_pipe_sequence(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (!can_parse_pipe_sequence(parser))
		return (NULL);
	root = node_create(NODETYPE_PIPE_SEQUENCE, NULL, 0);
	if (!root)
		return (NULL);
	while (TRUE)
	{
		child = parse_simple_command(parser);
		if (!child)
			return (parse_abort(parser, root, NULL));
		if (node_addchild(root, child))
			return (parse_abort(parser, root, child));
		if (parser_is_last_token(parser))
			return (root);
		if (parser->tok_curr->type != TOKENTYPE_PIPE)
			return (parse_abort(parser, root, NULL));
		parser->tok_curr++;
		root->n_tokens++;
	}
}
