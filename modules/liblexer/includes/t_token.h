/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:26 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKEN_H
# define T_TOKEN_H
# define N_TOKENTYPE 7

typedef struct s_token
{
	int		type;
	char	*content;
}	t_token;

typedef struct s_toks
{
	int		n_toks;
	t_token	*arr;
}	t_toks;

enum	e_tokentype
{
	TOKENTYPE_NULL = 0,
	TOKENTYPE_WORD,
	TOKENTYPE_REDIR_IN,
	TOKENTYPE_REDIR_OUT,
	TOKENTYPE_REDIR_IN_HERE,
	TOKENTYPE_REDIR_OUT_APPEND,
	TOKENTYPE_PIPE
};

void	token_destroy(t_toks *toks);

#endif
