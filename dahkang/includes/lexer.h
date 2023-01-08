#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "structures.h"

t_toks	*init_toks(char *str);

t_bool	is_space(char ch);
t_bool is_quote(char ch);
t_bool is_metachar(char ch);

t_bool	skip_space(char **str);
void	skip_inquote(char **str, char quote);
t_bool	skip_letter(char **str);
t_bool	skip_metachar(char **str);

#endif
