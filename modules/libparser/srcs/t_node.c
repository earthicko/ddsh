#include <stdlib.h>
#include "libft.h"
#include "t_node.h"

t_node	*node_create(int type, char *content, int n_tokens)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_node));
	new_node->childs = NULL;
	if (content)
	{
		new_node->content = ft_strdup(content);
		if (!(new_node->content))
			return (node_destroy(new_node));
	}
	new_node->type = type;
	new_node->n_tokens = n_tokens;
	return (new_node);
}

static void	node_destroy_internal(void *root)
{
	t_node	*node;

	node = root;
	if (!node)
		return ;
	if (node->childs)
		ft_lstclear(&(node->childs), node_destroy_internal);
	if (node->content)
		free(node->content);
	free(node);
}

t_node	*node_destroy(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->childs)
		ft_lstclear(&(node->childs), node_destroy_internal);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}

int	node_addchild(t_node *node, t_node *child)
{
	t_list	*new_child;

	new_child = ft_lstnew(child);
	if (!new_child)
		return (CODE_ERROR_MALLOC);
	ft_lstadd_back(&(node->childs), new_child);
	return (CODE_OK);
}

int	node_getntokens(t_node *node)
{
	int		n_tokens;
	t_list	*cursor;

	if (!node)
		return (0);
	n_tokens = node->n_tokens;
	cursor = node->childs;
	while (cursor)
	{
		n_tokens += node_getntokens(cursor->content);
		cursor = cursor->next;
	}
	return (n_tokens);
}
