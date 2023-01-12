#include <stdio.h>
#include <stdlib.h>

#include "libft_def.h"
#include "libft.h"
#include "t_node.h"
#include "lexer.h"
#include "parser.h"

int	get_n_redir(t_node *node);
void	node_print(t_node *root, int depth);

/*

static char	*get_node_typename(int type)
{
	char	*dict[11];

	dict[0] = "PIPE_SEQUENCE";
	dict[1] = "SIMPLE_COMMAND";
	dict[2] = "CMD_ELEMENT";
	dict[3] = "CMD_WORD";
	dict[4] = "IO_REDIRECT";
	dict[5] = "IO_FILE";
	dict[6] = "IO_OP_FILE";
	dict[7] = "FILENAME";
	dict[8] = "IO_HERE";
	dict[9] = "IO_OP_HERE";
	dict[10] = "HERE_END";
	return (dict[type]);
}

void	node_print_content(t_node *root)
{
	ft_printf("nodetype %s:%s, %d tokens\n",
		get_node_typename(root->type), root->content, node_getntokens(root));
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
	ft_printf("%snodetype %s:%s, %d tokens\n", prefix,
		get_node_typename(root->type), root->content, node_getntokens(root));
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
*/

int	get_n_redir(t_node *node)
{
	int		n_redir;
	t_list	*cursor;
	t_node	*curr;

	n_redir = 0;
	cursor = node->childs;
	while (cursor)
	{
		curr = cursor->content;
		curr = curr->childs->content;
		if (curr->type == NODETYPE_IO_REDIRECT)
			n_redir++;
		cursor = cursor->next;
	}
	return (n_redir);
}

int	main(void)
{
	t_node	*exec_tree;
	t_node	*simple_cmd;
	t_toks	toks;
	int		stat;

	printf("before lexer toks\n");
	stat = lexer("<a <b cat -e file >a > c >d", &toks);
	printf("before parse toks\n");
	exec_tree = parse_tokens(toks.arr, toks.n_toks);
	printf("exec_tree: %p\n", exec_tree);
	//node_print(exec_tree, 0);
	simple_cmd = exec_tree->childs->content;
	printf("simple cmd: %p", simple_cmd);
	//printf("n_redir: %d\n", get_n_redir(simple_cmd));
}
