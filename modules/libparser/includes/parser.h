#ifndef PARSER_H
# define PARSER_H
# include "t_node.h"
# include "t_token.h"

t_node	*parse_tokens(t_token *tokenarr, int n_tokens);

#endif
