/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "strutils.h"

# define ASCII_DEL '\177'
# define ASCII_STX '\002'
# define ASCII_ETX '\003'
# define SPLIT_MARKER "\002"
# define IFS_DEFAULT "\040\011\012"

enum	e_expand_option
{
	O_REMQUOTE = 1,
	O_PARSESQUOTE = 2,
	O_PARSEDQUOTE = 4,
	O_REMEMPTYVAR = 8,
	O_WORDSPLIT = 16
};

int	_do_expansion(char **buf, int option);
int	_do_tilde_expansion(char **buf);
int	_do_word_split(char *str, char ***buf);
int	_exit_compose(t_pchararr *strarr, char *word);
int	_compose_squote(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_dquote(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_envvar(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_str(char *str, int *pos, t_pchararr *strarr);
int	_mark_split(char **buf);

#endif
