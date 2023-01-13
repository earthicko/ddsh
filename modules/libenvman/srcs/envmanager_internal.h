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

int			envman_init(t_list **p_list, char **envp);
int			envman_clear(t_list **p_list);
int			envman_getval(t_list *envlist, char **buf, char *name);
int			envman_setval(t_list **envlist, char *name, char *val);
int			envman_unsetval(t_list **envlist, char *name);
int			envman_getenvp(t_list *envlist, char ***buf);

int			skip_and_append_squote(
				char *str, int *pos, t_pchararr *strarr, int quote_removal);
int			skip_and_append_envvar(
				char *str, int *pos, t_pchararr *strarr);
int			skip_and_append_str(
				char *str, int *pos, t_pchararr *strarr, int quote_removal);

#endif
