#ifndef STRUTILS_H
# define STRUTILS_H
# define PCHARARR_INITIAL_CAP 1

int			ft_strappend(char **body, const char *tail);
char		*ft_strmerge(int n_str, ...);

typedef struct s_pchararr
{
	int		len;
	int		cap;
	char	**data;
}	t_pchararr;

t_pchararr	*pchararr_create(void);
t_pchararr	*pchararr_destroy(t_pchararr *pchararr);
int			pchararr_expand(t_pchararr *pchararr);
int			pchararr_append(t_pchararr *pchararr, char *data);

#endif
