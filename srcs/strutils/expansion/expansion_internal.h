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
# define ASCII_DEL_STR "\177"
# define ASCII_DEL_CHAR '\177'

enum	e_expand_option
{
	O_REMQUOTE = 1,
	O_PARSESQUOTE = 2,
	O_PARSEDQUOTE = 4,
	O_REMEMPTYVAR = 8
};

int	_do_expansion(char **buf, int option);
int	_do_tilde_expansion(char **buf);
int	_exit_compose(t_pchararr *strarr, char *word);
int	_compose_squote(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_dquote(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_envvar(char *str, int *pos, t_pchararr *strarr, int option);
int	_compose_str(char *str, int *pos, t_pchararr *strarr);

#endif
