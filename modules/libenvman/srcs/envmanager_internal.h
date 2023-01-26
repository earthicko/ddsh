/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVMANAGER_INTERNAL_H
# define ENVMANAGER_INTERNAL_H
# include "libft_def.h"
# include "strutils.h"
# include "envmanager.h"
# define ENVSTR_DELIM_CHAR '='
# define ENVSTR_DELIM_STR "="
# define ENVMAN_N_SPECIALVAL 3
# define BUFFER_SIZE 64

enum e_envmanmode
{
	ENVMANMODE_INIT = 0,
	ENVMANMODE_CLEAR,
	ENVMANMODE_GETENTRY,
	ENVMANMODE_GETVAL,
	ENVMANMODE_SETVAL,
	ENVMANMODE_UNSETVAL,
	ENVMANMODE_GETENVP,
	ENVMANMODE_PRINTLIST_EXPORT,
	ENVMANMODE_PRINTLIST_DECLARE
};

typedef struct s_envmaninfo
{
	void	*buf;
	char	*name;
	char	*val;
	int		exp;
}	t_envmaninfo;

t_enventry	*_enventry_create(char *name, char *val, int exp);
void		_free_entry(void *content);
t_enventry	*_enventry_destroy(t_enventry *enventry);
t_list		*_find_list_with_entry(t_list *envlist, char *name);
int			_envman_addentry_str(
				t_list **p_list, char *str, int exp);
int			_envman_addentry_nameval(
				t_list **p_list, char *name, char *val, int exp);
t_enventry	*_enventry_getentry(t_list *envlist, char *name);

char		*envman_compose_envstr(t_enventry *entry);

int			_envmanager(int mode, t_envmaninfo *info);

int			_envman_init(t_list **p_list, char **envp);
int			_envman_clear(t_list **p_list);
int			_envman_getentry(t_list *envlist, t_enventry *buf, char *name);
int			_envman_getval(t_list *envlist, char **buf, char *name);
int			_envman_setval(t_list **envlist, char *name, char *val, int exp);
int			_envman_unsetval(t_list **envlist, char *name);
int			_envman_getenvp(t_list *envlist, char ***buf);
int			_envman_printlist_export(t_list *envlist);
int			_envman_printlist_declare(t_list *envlist);

int			_envman_isspecialval(char *name);
int			_envman_get_specialval(char *name, char **buf);

char		*_envman_get_time(void);
char		*_envman_get_pwd(void);
char		*_envman_get_hostname(void);

#endif
