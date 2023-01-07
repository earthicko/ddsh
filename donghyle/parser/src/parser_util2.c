#include "t_node.h"
#include "t_token.h"
#include <stddef.h>

static int	can_parse_io_file(t_token **current_token, t_token *last_token)
{
	if (*current_token == last_token)
		return (0);
	if ((*current_token)->type == TOKENTYPE_REDIR_IN)
		return (1);
	if ((*current_token)->type == TOKENTYPE_REDIR_OUT)
		return (1);
	if ((*current_token)->type == TOKENTYPE_REDIR_OUT_APPEND)
		return (1);
	return (0);
}

t_node	*parse_io_file(t_token **current_token, t_token *last_token)
{
	t_node	*root;
	t_node	*child;

	if (!can_parse_io_file(current_token, last_token))
		return (NULL);
	(*current_token)++;
	child = parse_filename(current_token, last_token);
	if (!child)
	{
		(*current_token)--;
		return (NULL);
	}
	root = create_node(NODETYPE_IO_FILE, (*current_token)->content);
	if (!root || addchild_node(root, child) < 0)
	{
		if (root)
			destroy_node(root);
		(*current_token) -= 2;
		destroy_node(child);
		return (NULL);
	}
	return (root);
}

t_node	*parse_io_redirect(t_token **current_token, t_token *last_token)
{
	t_node	*root;
	t_node	*child;

	root = create_node(NODETYPE_IO_REDIRECT, "");
	if (!root)
		return (NULL);
	child = parse_io_file(current_token, last_token);
	if (child)
	{
		if (addchild_node(root, child) < 0)
			return (destroy_node(root));
		return (root);
	}
	child = parse_io_here(current_token, last_token);
	if (child)
	{
		if (addchild_node(root, child) < 0)
			return (destroy_node(root));
		return (root);
	}
	return (destroy_node);
}
