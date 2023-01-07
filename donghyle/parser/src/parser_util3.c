#include "t_node.h"
#include "t_token.h"
#include <stddef.h>

t_node	*parse_cmd_element(t_token **current_token, t_token *last_token)
{
	t_node	*root;

	if ((*current_token)->type == TOKENTYPE_WORD)
		return (create_node(NODETYPE_CMD_ELEMENT, (*current_token)->content));
	return (parse_io_redirect(current_token, last_token));
}

t_node	*parse_simple_command(t_token **current_token, t_token *last_token)
{
	t_node	*root;
	t_node	*child;

	root = create_node(NODETYPE_SIMPLE_COMMAND, "");
	if (!root)
		return (NULL);
	while (1)
	{
		child = parse_cmd_element(current_token, last_token);
		if (!child)
			return (root);
		if (addchild_node(root, child))
			return (destroy_node(root));
	}
}

t_node	*parse_pipe_sequence(t_token **current_token, t_token *last_token)
{
	t_node	*root;
	t_node	*child;

	root = create_node(NODETYPE_PIPE_SEQUENCE, "|");
	if (!root)
		return (NULL);
	while (1)
	{
		child = parse_simple_command(current_token, last_token);
		if (!child || addchild_node(root, child) < 0)
			return (destroy_node(root));
		if (*current_token == last_token)
			return (root);
		if ((*current_token)->type != TOKENTYPE_PIPE)
			return (destroy_node(root));
	}
	return (destroy_node(root));
}
