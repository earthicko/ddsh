#include "libft.h"

int	is_valid_name(char *str)
{
	if (!str || ft_strlen(str) == 0 || ft_isdigit(str[0]))
		return (FALSE);
	while (*str)
	{
		if (!(*str == '_' || ft_isalnum(*str)))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
