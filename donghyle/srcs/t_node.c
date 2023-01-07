#include "t_node.h"
#include "libft.h"
#include <stdlib.h>

t_node	*create_node(int type, char *content)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_node));
	new_node->childs = ft_lstnew(NULL);
	new_node->content = ft_strdup(content);
	if (!(new_node->childs && new_node->content))
		return (destroy_node(new_node));
	new_node->type = type;
	return (new_node);
}

t_node	*destroy_node(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->childs)
		ft_lstclear(&(node->childs), destroy_node);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}

int	addchild_node(t_node *node, t_node *child)
{
	t_list	*new_child;

	new_child = ft_lstnew(child);
	if (!new_child)
		return (-1);
	ft_lstadd_back(&(node->childs), new_child);
	return (0);
}
