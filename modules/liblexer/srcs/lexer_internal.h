/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:26 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include <stdlib.h>
# include "t_token.h"
# include "libft_def.h"
# include "lexer.h"

# define UNCLOSED_QUOTE -1

int	_get_n_toks(char *str);
int	_get_word_len(char *str);
int	_get_token_type(char *str);

int	_is_space(char ch);
int	_is_quote(char ch);
int	_is_metachar(char ch);

int	_get_len_space(char *str);
int	_get_len_inquotes(char *str, char quote);
int	_get_len_normal(char *str);
int	op_len(char *str);

#endif
