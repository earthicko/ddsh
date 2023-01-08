#include "t_node.h"
#include "t_token.h"
#include "parser_internal.h"
#include <stddef.h>

t_node	*parse_here_end(t_parser *parser)
{
	t_node	*root;

	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type != TOKENTYPE_WORD)
		return (NULL);
	root = node_create(NODETYPE_HERE_END, parser->tok_curr->content, 1);
	if (!root)
		return (NULL);
	parser_increment_token(parser, 1);
	return (root);
}

t_node	*parse_io_here(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type != TOKENTYPE_REDIR_IN_HERE)
		return (NULL);
	root = node_create(NODETYPE_IO_HERE, parser->tok_curr->content, 1);
	if (!root)
		return (parse_abort(parser, NULL, NULL));
	parser_increment_token(parser, 1);
	child = parse_here_end(parser);
	if (!child)
		return (parse_abort(parser, root, NULL));
	if (node_addchild(root, child))
		return (parse_abort(parser, root, child));
	return (root);
}

t_node	*parse_filename(t_parser *parser)
{
	t_node	*root;

	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type != TOKENTYPE_WORD)
		return (NULL);
	root = node_create(NODETYPE_FILENAME, parser->tok_curr->content, 1);
	if (!root)
		return (NULL);
	parser_increment_token(parser, 1);
	return (root);
}
