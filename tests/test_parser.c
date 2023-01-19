#include "parser.h"
#include "t_node.h"
#include "heredoc.h"
#include "testers.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void	set_tokens(t_token *p_tokens, int *n_tokens)
{
	*n_tokens = 8;
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

int	get_rand_int(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

void	swap_token(t_token *p_tokens, int i, int j)
{
	int		ibuf;
	char	*cbuf;

	ibuf = p_tokens[i].type;
	p_tokens[i].type = p_tokens[j].type;
	p_tokens[j].type = ibuf;
	cbuf = p_tokens[i].content;
	p_tokens[i].content = p_tokens[j].content;
	p_tokens[j].content = cbuf;
}

void	shuffle(t_token *p_tokens, int n_tokens, int n_times)
{
	int	i;
	int	s;
	int	e;

	i = 0;
	while (i < n_times)
	{
		s = get_rand_int(0, n_tokens - 1);
		e = get_rand_int(0, n_tokens - 1);
		swap_token(p_tokens, s, e);
		i++;
	}
}

// cat << EOF | > result grep "hello"
int	main(void)
{
	t_node	*root;
	t_token	tokens[10];
	int		n_tokens;

	srand(time(NULL));
	set_tokens(tokens, &n_tokens);
	shuffle(tokens, n_tokens, 10);
	print_tokens(tokens, n_tokens);
	root = parse_tokens(tokens, 8);
	if (root)
	{
		node_print(root, 0);
		printf("%p\n", ((t_node *)(root->childs->content)));
		node_destroy(root);
	}
	system("leaks test_parser");
	return (0);
}
