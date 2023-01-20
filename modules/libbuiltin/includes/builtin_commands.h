#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

int	builtin_echo(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(char **argv);
int	builtin_export(char **argv);
int	builtin_unset(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv);

#endif
