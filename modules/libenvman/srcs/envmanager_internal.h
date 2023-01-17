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

void		_free_entry(void *content);
t_list		*_find_list_with_entry(t_list *envlist, char *name);
int			_envman_addentry(t_list **p_list, char *env);
t_enventry	*_envman_getentry(t_list *envlist, char *name);

int			_envmanager(char **envp, void *buf, char *name, char *val);

// TODO: internal 함수 앞에 _
int			_envman_init(t_list **p_list, char **envp);
int			_envman_clear(t_list **p_list);
int			_envman_getval(t_list *envlist, char **buf, char *name);
int			_envman_setval(t_list **envlist, char *name, char *val);
int			_envman_unsetval(t_list **envlist, char *name);
int			_envman_getenvp(t_list *envlist, char ***buf);

#endif
