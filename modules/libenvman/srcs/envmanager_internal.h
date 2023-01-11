#ifndef ENVMANAGER_INTERNAL_H
# define ENVMANAGER_INTERNAL_H
# include "libft_def.h"
# define ENVSTR_DELIM_CHAR '='
# define ENVSTR_DELIM_STR "="

typedef struct s_enventry
{
	char	*name;
	char	*val;
}	t_enventry;

int			envman_split_envstr(char *str, char **ret_name, char **ret_val);
char		*envman_compose_envstr(char *name, char *val);

void		free_entry(void *content);
t_list		*find_list_with_entry(t_list *envlist, char *name);
int			envman_addentry(t_list **p_list, char *env);
t_enventry	*envman_getentry(t_list *envlist, char *name);

int			envman_init(t_list **p_list, char **envp);
int			envman_clear(t_list **p_list);
int			envman_getval(t_list *envlist, char **buf, char *name);
int			envman_setval(t_list **envlist, char *name, char *val);
int			envman_unsetval(t_list **envlist, char *name);
int			envman_getenvp(t_list *envlist, char ***buf);

#endif
