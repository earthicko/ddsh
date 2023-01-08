#include "../includes/lexer.h"

t_bool	is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n')
		return (TRUE);
	else
		return (FALSE);
}

t_bool is_quote(char ch)
{
	if (ch == '\'' || ch == '\"')
		return (TRUE);
	else
		return (FALSE);
}

t_bool is_metachar(char ch)
{
	if (ch == '<' || ch == '>' || ch =='|')
		return (TRUE);
	else
		return (FALSE);
}
