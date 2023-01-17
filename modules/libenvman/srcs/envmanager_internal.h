#ifndef ENVMANAGER_INTERNAL_H
# define ENVMANAGER_INTERNAL_H
# include "libft_def.h"
# include "strutils.h"
# include "envmanager.h"
# define ENVSTR_DELIM_CHAR '='
# define ENVSTR_DELIM_STR "="

typedef struct s_enventry
{
	char	*name;
	char	*val;
}	t_enventry;

void		free_entry(void *content);
t_list		*find_list_with_entry(t_list *envlist, char *name);
int			envman_addentry(t_list **p_list, char *env);
t_enventry	*envman_getentry(t_list *envlist, char *name);

int			envmanager(char **envp, void *buf, char *name, char *val);

int			envman_init_(t_list **p_list, char **envp);
int			envman_clear_(t_list **p_list);
int			envman_getval_(t_list *envlist, char **buf, char *name);
int			envman_setval_(t_list **envlist, char *name, char *val);
int			envman_unsetval_(t_list **envlist, char *name);
int			envman_getenvp_(t_list *envlist, char ***buf);

#endif
