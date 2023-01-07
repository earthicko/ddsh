#ifndef T_TOKEN_H
# define T_TOKEN_H

typedef struct s_token
{
	int		type;
	char	*content;
	int		expansion;
}	t_token;

enum	e_tokentype
{
	TOKENTYPE_WORD = 0,
	TOKENTYPE_REDIR_IN,
	TOKENTYPE_REDIR_OUT,
	TOKENTYPE_REDIR_IN_HERE,
	TOKENTYPE_REDIR_OUT_APPEND,
	TOKENTYPE_PIPE,
	TOKENTYPE_AND,
	TOKENTYPE_OR
};

#endif
