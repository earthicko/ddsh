#include "t_node.h"
#include "libft.h"
#include <stdlib.h>

static char	*get_node_typename(int type)
{
	switch (type)
	{
	case 0:
		return ("PIPE_SEQUENCE");
		break;
	case 1:
		return ("SIMPLE_COMMAND");
		break;
	case 2:
		return ("CMD_ELEMENT");
		break;
	case 3:
		return ("IO_REDIRECT");
		break;
	case 4:
		return ("IO_FILE");
		break;
	case 5:
		return ("FILENAME");
		break;
	case 6:
		return ("IO_HERE");
		break;
	case 7:
		return ("HERE_END");
		break;
	default:
		return ("");
		break;
	}
}

void	node_print_content(t_node *root)
{
	ft_printf("node type \"%s\", content \"%s\"\n",
		get_node_typename(root->type), root->content);
}

static void	print_childs(t_node *root, int depth);

void	node_print(t_node *root, int depth)
{
	char	*prefix;
	char	*temp;
	int		i;

	if (!root)
		return ;
	prefix = ft_strdup("");
	i = 0;
	while (i < depth)
	{
		temp = ft_strjoin(prefix, "\t");
		free(prefix);
		prefix = temp;
		i++;
	}
	ft_printf("%snode type \"%s\", content \"%s\"\n",
		prefix, get_node_typename(root->type), root->content);
	ft_printf("%schilds:\n", prefix);
	free(prefix);
	print_childs(root, depth + 1);
}

static void	print_childs(t_node *root, int depth)
{
	t_list	*cursor;

	cursor = root->childs;
	while (cursor)
	{
		node_print(cursor->content, depth);
		cursor = cursor->next;
	}
}
