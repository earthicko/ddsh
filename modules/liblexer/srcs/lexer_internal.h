#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include <stdlib.h>
# include "t_token.h"
# include "libft_def.h"
# include "lexer.h"

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
