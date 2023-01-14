#ifndef ENVMANAGER_H
# define ENVMANAGER_H

int		envmanager(char **envp, void *buf, char *name, char *val);
int		envman_replace_envvar(char **buf, int quote_removal);
int		envman_split_envstr(char *str, char **ret_name, char **ret_val);
char	*envman_compose_envstr(char *name, char *val);
int		exit_stat_manager(int new_stat);

#endif
