#include "../includes/lexer.h"
#include "../libft/includes/libft.h"

#include <stdio.h>

int	space_len(char *str)
{
	int	len;
	
	len = 0;
	while (str[len] && is_space(str[len]))
		len++;
	return (len);
}

int	inquote_len(char *str, char quote)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != quote)
		len++;
	return (len);
}

int	letter_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_quote(str[len])
			&& !is_space(str[len]) && !is_metachar(str[len]))
		len++;
	return (len);
}

int	op_len(char *str)
{
	int	len;

	len = 0;

	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		len = 2;
	else
		len = 1;
	return (len);
}
