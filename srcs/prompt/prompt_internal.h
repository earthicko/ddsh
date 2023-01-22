#ifndef PROMPT_INTERNAL_H
# define PROMPT_INTERNAL_H
# define CODE_CONTINUE 1

int	prompt_init(void);
int	prompt_getstr(char **buf);
int	prompt_gettokens(char *str, t_toks *toks);
int	prompt_getparsetree(t_toks *toks, t_node **buf);
int	prompt_execute(t_node *parse_tree);

#endif
