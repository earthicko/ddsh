#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "structures.h"

int		get_n_toks(char *str);
t_toks	*init_toks(char *str);

int		get_word_len(char *str);
int		get_token_type(char *str);

t_bool	is_space(char ch);
t_bool	is_quote(char ch);
t_bool	is_metachar(char ch);

int		space_len(char *str);
int		inquote_len(char *str, char quote);
int		letter_len(char *str);
int		op_len(char *str);

#endif
