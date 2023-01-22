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

int		get_n_toks(char *str);
int		get_word_len(char *str);
int		get_token_type(char *str);

t_bool	is_space(char ch);
t_bool	is_quote(char ch);
t_bool	is_metachar(char ch);

int		space_len(char *str);
int		inquote_len(char *str, char quote);
int		letter_len(char *str);
int		op_len(char *str);

#endif
