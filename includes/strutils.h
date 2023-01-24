/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:47:09 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:47:15 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUTILS_H
# define STRUTILS_H
# include "t_node.h"
# define PCHARARR_INITIAL_CAP 1

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
char		*pchararr_merge(t_pchararr *strarr);
void		pchararr_free_all_pchars(t_pchararr *strarr);

int			remove_quotes(char **buf);

int			is_valid_name(char *str);

int			is_builtin_command(char *str);

int			find_exec(char **buf);

int			do_shell_expansion(char **buf);
int			do_heredoc_expansion(char **buf);

int			expand_node(t_node *root);

#endif
