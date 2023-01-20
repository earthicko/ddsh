#include <stddef.h>
#include "libft.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_addchild_and_return(t_parser *p, t_node *root, t_node *child)
{
	if (node_addchild(root, child))
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (_parse_abort(p, root, child));
	}
	return (root);
}

int	_parse_terminal_and_addchild(t_parser *p, int n_t, t_node *root)
{
	int		stat;
	t_node	*child;

	child = _parse_terminal(p, n_t);
	if (!child)
	{
		_parse_abort(p, root, NULL);
		return (CODE_ERROR_GENERIC);
	}
	stat = node_addchild(root, child);
	if (stat)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		_parse_abort(p, root, child);
		return (stat);
	}
	return (CODE_OK);
}

t_node	*_parse_abort(t_parser *p, t_node *root, t_node *child)
{
	int	rewind_counter;

	rewind_counter = 0;
	if (root)
	{
		rewind_counter += node_getntokens(root);
		node_destroy(root);
	}
	if (child)
	{
		rewind_counter += node_getntokens(child);
		node_destroy(child);
	}
	p->tok_curr -= rewind_counter;
	return (NULL);
}

// TODO: 에러 메시지 통일
void	_parse_perror(t_parser *p)
{
	if (p->exit_stat)
	{
		ft_print_error("parser", p->exit_stat);
	}
	else
	{
		if (p->last_error_loc == p->tok_last)
			p->last_error_loc--;
		ft_dprintf(2, "syntax error near unexpected token `%s`\n",
			p->last_error_loc->content);
	}
}
