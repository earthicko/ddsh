#include "parser.h"
#include <stdlib.h>

void	node_print(t_node *root, int depth);

int main(void)
{
	t_node	*root;
	t_token	tokens[10];

	// cat << EOF | > result grep "hello"
	tokens[0].content = "cat";
	tokens[0].type = TOKENTYPE_WORD;
	tokens[1].content = "<<";
	tokens[1].type = TOKENTYPE_REDIR_IN_HERE;
	tokens[2].content = "EOF";
	tokens[2].type = TOKENTYPE_WORD;
	tokens[3].content = "|";
	tokens[3].type = TOKENTYPE_PIPE;
	tokens[4].content = ">";
	tokens[4].type = TOKENTYPE_REDIR_OUT;
	tokens[5].content = "result";
	tokens[5].type = TOKENTYPE_WORD;
	tokens[6].content = "grep";
	tokens[6].type = TOKENTYPE_WORD;
	tokens[7].content = "\"hello\"";
	tokens[7].type = TOKENTYPE_WORD;

	root = parse_tokens(tokens, 8);
	node_print(root, 0);
	node_destroy(root);
	system("leaks minishell");
	return 0;
}
