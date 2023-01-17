#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

int			_do_shell_expansion(
				char **buf, int remove_quote, int squote, int dquote);
int			_exit_compose(
				t_pchararr *strarr, char *word);
int			_compose_squote(
				char *str, int *pos, t_pchararr *strarr, int remove_quote);
int			_compose_dquote(
				char *str, int *pos, t_pchararr *strarr, int remove_quote);
int			_compose_envvar(
				char *str, int *pos, t_pchararr *strarr);
int			_compose_str(
				char *str, int *pos, t_pchararr *strarr);

#endif
