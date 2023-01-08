#ifndef T_NODE_H
# define T_NODE_H

# include "libft_def.h"

typedef struct s_node
{
	t_list	*childs;
	int		type;
	char	*content;
	int		n_tokens;
}	t_node;

enum e_nodetype
{
	NODETYPE_PIPE_SEQUENCE = 0,
	NODETYPE_SIMPLE_COMMAND,
	NODETYPE_CMD_ELEMENT,
	NODETYPE_IO_REDIRECT,
	NODETYPE_IO_FILE,
	NODETYPE_FILENAME,
	NODETYPE_IO_HERE,
	NODETYPE_HERE_END,
};

t_node	*create_node(int type, char *content, int n_tokens);
t_node	*destroy_node(t_node *node);
int		addchild_node(t_node *node, t_node *child);
int		getntokens_node(t_node *node);

void	print_node_content(t_node *root);
#endif
