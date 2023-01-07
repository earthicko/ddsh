#include "t_node.h"
#include "t_token.h"
#include <stdlib.h>

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

t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_token	*token_p;
	t_token	*last_token;
	t_node	*root;

	token_p = tokenarr;
	last_token = tokenarr + n_tokens;
	root = parse_pipe_sequence(&token_p, last_token);
	return (root);
}
