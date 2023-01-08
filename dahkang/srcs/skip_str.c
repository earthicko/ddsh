#include "../includes/lexer.h"
#include "../libft/includes/libft.h"

t_bool	skip_space(char **str)
{
	int	skipped;
	
	skipped = 0;
	if (is_space(**str))
		skipped = 1;
	while (**str && is_space(**str))
		(*str)++;
	return (skipped);
}

void	skip_inquote(char **str, char quote)
{
	while (**str && **str != quote)
		(*str)++;
}

t_bool	skip_letter(char **str)
{
	int	skipped;

	skipped = 0;
	if (**str && !is_quote(**str) && !is_space(**str) && !is_metachar(**str))
		skipped = 1;
	while (**str && !is_quote(**str)
			&& !is_space(**str) && !is_metachar(**str))
		(*str)++;
	return (skipped);
}

t_bool	skip_metachar(char **str)
{
	int	skipped = 1;

	if (ft_strncmp(*str, ">>", 2) == 0)
		(*str) += 2;
	else if (ft_strncmp(*str, "<<", 2) == 0)
		(*str) += 2;
	else if (**str == '>')
		(*str)++;
	else if (**str == '<')
		(*str)++;
	else if (**str == '|')
		(*str)++;
	else
		skipped = 0;
	return (skipped);
}
