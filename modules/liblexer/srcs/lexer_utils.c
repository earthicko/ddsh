#include "lexer_internal.h"

int	get_word_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len] && !is_space(str[len]) && !is_metachar(str[len]))
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len++];
			len += inquote_len(str + len, quote);
			if (str[len] != quote)
				return (-1);
			quote = 0;
			len++;
		}
		len += letter_len(str + len);
	}
	return (len);
}

int	get_token_type(char *str)
{
	if (*str == 0)
		return (TOKENTYPE_NULL);
	if (*str == '|')
		return (TOKENTYPE_PIPE);
	else if (*str == '<' && *(str + 1) == '<')
		return (TOKENTYPE_REDIR_IN_HERE);
	else if (*str == '>' && *(str + 1) == '>')
		return (TOKENTYPE_REDIR_OUT_APPEND);
	else if (*str == '<')
		return (TOKENTYPE_REDIR_IN);
	else if (*str == '>')
		return (TOKENTYPE_REDIR_OUT);
	else
		return (TOKENTYPE_WORD);
}
