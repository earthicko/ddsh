#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H
# include "t_node.h"
# include "t_token.h"
# include "parser.h"

typedef struct s_parser
{
	t_token	*tok_start;
	t_token	*tok_curr;
	t_token	*tok_last;
	int		n_tokens;
}	t_parser;

int		parser_is_last_token(t_parser *parser);

void	map_setter_cmd_word(int *token_map);
void	map_setter_io_op_file(int *token_map);
void	map_setter_filename(int *token_map);
void	map_setter_io_op_here(int *token_map);
void	map_setter_here_end(int *token_map);

t_node	*parse_addchild_and_return(t_parser *p, t_node *root, t_node *child);
int		parse_terminal_and_addchild(t_parser *p, int n_t, t_node *root);
t_node	*parse_abort(t_parser *parser, t_node *root, t_node *child);

t_node	*parse_terminal(t_parser *parser, int nodetype);
t_node	*parse_simple_command(t_parser *parser);
t_node	*parse_pipe_sequence(t_parser *parser);
t_node	*parse_io_redirect(t_parser *parser);
t_node	*parse_io_here(t_parser *parser);
t_node	*parse_io_file(t_parser *parser);
t_node	*parse_cmd_element(t_parser *parser);

#endif
