#ifndef TESTERS_H
# define TESTERS_H
# include "t_token.h"
# include "t_node.h"

void	node_print_content(t_node *root);
void	node_print(t_node *root, int depth);

void	print_tokens(t_token *p_token, int n_tokens);

#endif
