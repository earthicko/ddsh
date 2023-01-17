#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

int			skip_and_append_squote(
				char *str, int *pos, t_pchararr *strarr, int remove_quote);
int			skip_and_append_dquote(
				char *str, int *pos, t_pchararr *strarr, int remove_quote);
int			skip_and_append_envvar(
				char *str, int *pos, t_pchararr *strarr);
int			skip_and_append_str(
				char *str, int *pos, t_pchararr *strarr, int remove_quote);

#endif
