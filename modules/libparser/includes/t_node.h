#ifndef T_NODE_H
# define T_NODE_H
# include "libft_def.h"
# define N_NODETYPE 11

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
	NODETYPE_CMD_WORD,
	NODETYPE_IO_REDIRECT,
	NODETYPE_IO_FILE,
	NODETYPE_IO_OP_FILE,
	NODETYPE_FILENAME,
	NODETYPE_IO_HERE,
	NODETYPE_IO_OP_HERE,
	NODETYPE_HERE_END,
};

t_node	*node_create(int type, char *content, int n_tokens);
t_node	*node_destroy(t_node *node);
int		node_addchild(t_node *node, t_node *child);
int		node_getntokens(t_node *node);

#endif
