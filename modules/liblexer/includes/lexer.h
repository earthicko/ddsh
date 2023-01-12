#ifndef LEXER_H
# define LEXER_H

# include "t_token.h"

int		lexer(char *str, t_toks *toks);
void	token_destroy(t_toks *toks);

#endif
