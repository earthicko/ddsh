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

t_list		*find_list_with_entry(t_list *envlist, char *name);

t_enventry	*enventry_destroy(t_enventry *enventry);
void		free_entry(void *content);
int			envmanager_addentry(t_list **p_list, char *env);
t_enventry	*envmanager_getentry(t_list *envlist, char *name);
int			envmanager_getval(t_list *envlist, char **buf, char *name);
char		*compose_envstr(char *name, char *val);
int			envmanager_setval(t_list **envlist, char *name, char *val);
int			envmanager_unsetval(t_list **envlist, char *name);
int			envmanager_getenvp(t_list *envlist, char ***buf);

#endif
