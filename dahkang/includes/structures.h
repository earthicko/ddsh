#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_token
{
	int		type;
	char	*content;
	int		expansion;
}	t_token;

typedef struct s_toks
{
	int		n_toks;
	t_token	*arr;
}	t_toks;

enum	e_tokentype
{
	TOKENTYPE_WORD = 0,
	TOKENTYPE_REDIR_IN,
	TOKENTYPE_REDIR_OUT,
	TOKENTYPE_REDIR_IN_HERE,
	TOKENTYPE_REDIR_OUT_APPEND,
	TOKENTYPE_PIPE
};

#endif
