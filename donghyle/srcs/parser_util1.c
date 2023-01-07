#include "t_node.h"
#include "t_token.h"
#include <stddef.h>

t_node	*parse_here_end(t_token **current_token, t_token *last_token)
{
	t_node	*root;

	if (*current_token == last_token)
		return (NULL);
	if ((*current_token)->type != TOKENTYPE_WORD)
		return (NULL);
	root = create_node(NODETYPE_HERE_END, (*current_token)->content);
	if (!root)
		return (NULL);
	// quote removal needed?
	(*current_token)++;
	return (root);
}

t_node	*parse_io_here(t_token **current_token, t_token *last_token)
{
	t_node	*root;
	t_node	*child;

	if (*current_token == last_token)
		return (NULL);
	if ((*current_token)->type != TOKENTYPE_REDIR_IN_HERE)
		return (NULL);
	(*current_token)++;
	child = parse_here_end(current_token, last_token);
	if (!child)
	{
		(*current_token)--;
		return (NULL);
	}
	root = create_node(NODETYPE_IO_HERE, (*current_token)->content);
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

t_node	*parse_filename(t_token **current_token, t_token *last_token)
{
	t_node	*root;

	if (*current_token == last_token)
		return (NULL);
	if ((*current_token)->type != TOKENTYPE_WORD)
		return (NULL);
	root = create_node(NODETYPE_FILENAME, (*current_token)->content);
	if (!root)
		return (NULL);
	(*current_token)++;
	return (root);
}
