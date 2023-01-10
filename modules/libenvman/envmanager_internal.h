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

int			split_envstring(char *str, char **ret_name, char **ret_val);
char		*compose_envstr(char *name, char *val);

void		free_entry(void *content);
t_list		*find_list_with_entry(t_list *envlist, char *name);
int			envmanager_addentry(t_list **p_list, char *env);
t_enventry	*envmanager_getentry(t_list *envlist, char *name);

int			envmanager_init(t_list **p_list, char **envp);
int			envmanager_clear(t_list **p_list);
int			envmanager_getval(t_list *envlist, char **buf, char *name);
int			envmanager_setval(t_list **envlist, char *name, char *val);
int			envmanager_unsetval(t_list **envlist, char *name);
int			envmanager_getenvp(t_list *envlist, char ***buf);

#endif
