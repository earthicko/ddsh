#ifndef PARSER_H
# define PARSER_H
# include "t_node.h"
# include "t_token.h"

typedef struct s_parser
{
	t_token	*tok_start;
	t_token	*tok_curr;
	t_token	*tok_last;
	int		n_tokens;
}	t_parser;

t_node	*parse_tokens(t_token *tokenarr, int n_tokens);

#endif
