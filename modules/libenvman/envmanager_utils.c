#include "envmanager_internal.h"
#include "libft.h"
#include <stdlib.h>

char	*compose_envstr(char *name, char *val)
{
	char	*base;
	char	*temp;

	base = ft_strdup(name);
	if (!base)
		return (NULL);
	temp = ft_strjoin(base, ENVSTR_DELIM_STR);
	free(base);
	if (!temp)
		return (NULL);
	base = temp;
	temp = ft_strjoin(base, val);
	free(base);
	if (!temp)
		return (NULL);
	return (temp);
}

int	split_envstring(char *str, char **ret_name, char **ret_val)
{
	size_t	i_split;
	size_t	len_str;

	len_str = ft_strlen(str);
	i_split = 0;
	while (i_split < len_str)
	{
		if (str[i_split] == ENVSTR_DELIM_CHAR)
			break ;
		i_split++;
	}
	if (i_split == len_str)
		return (CODE_ERROR_DATA);
	*ret_name = ft_substr(str, 0, i_split);
	*ret_val = ft_substr(str, i_split + 1, len_str - i_split - 1);
	if (!(*ret_name && *ret_val))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
