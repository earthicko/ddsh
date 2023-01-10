#include "envmanager_internal.h"
#include "libft.h"
#include <stdlib.h>

static int	split_envstring(char *str, char **ret_name, char **ret_val)
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

int	envmanager_addentry(t_list **p_list, char *env)
{
	t_list		*newlst;
	t_enventry	*entry;
	int			stat;

	entry = malloc(sizeof(t_enventry));
	if (!entry)
		return (CODE_ERROR_MALLOC);
	ft_memset(entry, 0, sizeof(entry));
	stat = split_envstring(env, &(entry->name), &(entry->val));
	if (stat)
	{
		enventry_destroy(entry);
		return (stat);
	}
	newlst = ft_lstnew(entry);
	if (!newlst)
	{
		enventry_destroy(entry);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(p_list, newlst);
	return (CODE_OK);
}
