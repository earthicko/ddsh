#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H
# include "t_node.h"
# include "t_token.h"
# include "parser.h"

int		parser_is_last_token(t_parser *parser);
void	parser_increment_token(t_parser *parser, int n);

t_node	*parse_abort(t_parser *parser, t_node *root, t_node *child);
t_node	*parse_io_here(t_parser *parser);
t_node	*parse_io_redirect(t_parser *parser);
t_node	*parse_filename(t_parser *parser);
t_node	*parse_pipe_sequence(t_parser *parser);

#endif
