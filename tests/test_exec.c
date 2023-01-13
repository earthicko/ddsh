#include <stdio.h>
#include <stdlib.h>

#include "libft_def.h"
#include "libft.h"
#include "t_node.h"
#include "lexer.h"
#include "parser.h"

int		get_n_redir(t_node *node);
void	node_print(t_node *root, int depth);

//유효한 인풋만 넣어야 함, 유효하지 않은 경우 쓰레기값이 전달될 것임
static void	test_get_n_redir(char *str, t_toks *toks)
{
	t_node	*root;
	t_node	*simple_cmd;
	int		stat;

	printf("\n\n");

	stat = lexer(str, toks);
	if (stat)
	{
		printf("Failed to build toks arr in lexer\n\n");
		printf("\n>=========================<\n\n");
		return ;
	}
	root = parse_tokens(toks->arr, toks->n_toks);
	//node_print(root, 0);
	printf("root->content: %s\n", root->content);
	simple_cmd = root->childs->content;
	printf("input: %s\n\n", str);
	printf("n_redir: %d\n\n", get_n_redir(simple_cmd));
	node_destroy(root);
	token_destroy(toks);
	printf("\n>=========================<\n\n");
}

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
	t_toks	toks;

	printf(">=========TEST GET_N_REDIR<=========\n");
	test_get_n_redir("<a <b cat -e file >a > c >d", &toks);
	test_get_n_redir("cat <a file -e file <a >b <<b", &toks);
	test_get_n_redir("cat <a file -e file <a >b <<b", &toks);
	test_get_n_redir("\"cat <a file -e file <a >b <<b", &toks);
	test_get_n_redir("cat <a >b <<b | cat -e > file", &toks);
	system("leaks test_exec");
}
