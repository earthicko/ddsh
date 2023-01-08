#include "parser.h"
#include "t_node.h"
#include <stdlib.h>

void	set_tokens(t_token *p_tokens)
{
	p_tokens[0].content = "cat";
	p_tokens[0].type = TOKENTYPE_WORD;
	p_tokens[1].content = "<<";
	p_tokens[1].type = TOKENTYPE_REDIR_IN_HERE;
	p_tokens[2].content = "EOF";
	p_tokens[2].type = TOKENTYPE_WORD;
	p_tokens[3].content = "|";
	p_tokens[3].type = TOKENTYPE_PIPE;
	p_tokens[4].content = ">";
	p_tokens[4].type = TOKENTYPE_REDIR_OUT;
	p_tokens[5].content = "result";
	p_tokens[5].type = TOKENTYPE_WORD;
	p_tokens[6].content = "grep";
	p_tokens[6].type = TOKENTYPE_WORD;
	p_tokens[7].content = "\"hello\"";
	p_tokens[7].type = TOKENTYPE_WORD;
}

// cat << EOF | > result grep "hello"
int	main(void)
{
	t_node	*root;
	t_token	tokens[10];

	set_tokens(tokens);
	root = parse_tokens(tokens, 8);
	node_print(root, 0);
	node_destroy(root);
	system("leaks minishell");
	return (0);
}
