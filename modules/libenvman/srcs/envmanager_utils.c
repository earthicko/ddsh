#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

char	*envman_compose_envstr(char *name, char *val)
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

static size_t	find_equal_sign(char *str, size_t len)
{
	size_t	i_split;

	i_split = 0;
	while (i_split < len)
	{
		if (str[i_split] == ENVSTR_DELIM_CHAR)
			return (i_split);
		i_split++;
	}
}

static int	split_envstr_abort(char **name, char **val, int stat)
{
	if (*name)
		free(*name);
	if (*val)
		free(*val);
	*name = NULL;
	*val = NULL;
	return (stat);
}

int	envman_split_envstr(char *str, char **ret_name, char **ret_val)
{
	size_t	i_split;
	size_t	len_str;

	len_str = ft_strlen(str);
	i_split = find_equal_sign(str, len_str);
	if (i_split == len_str)
		return (CODE_ERROR_DATA);
	*ret_name = ft_substr(str, 0, i_split);
	*ret_val = ft_substr(str, i_split + 1, len_str - i_split - 1);
	if (!(*ret_name && *ret_val))
		return (split_envstr_abort(ret_name, ret_val, CODE_ERROR_MALLOC));
	if (!is_valid_name(*ret_name))
		return (split_envstr_abort(ret_name, ret_val, CODE_ERROR_DATA));
	return (CODE_OK);
}
