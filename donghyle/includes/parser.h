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
	int		rewind_counter;
}	t_parser;

int		parser_is_last_token(t_parser *parser);
void	parser_increment_token(t_parser *parser, int n);

t_node	*parse_abort(t_parser *parser, t_node *root, t_node *child);
t_node	*parse_io_here(t_parser *parser);
t_node	*parse_io_redirect(t_parser *parser);
t_node	*parse_filename(t_parser *parser);
t_node	*parse_pipe_sequence(t_parser *parser);
t_node	*parse_tokens(t_token *tokenarr, int n_tokens);

#endif
