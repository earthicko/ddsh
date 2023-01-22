/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	get_n_toks(char *str)
{
	int		n_toks;
	int		tok_type;
	int		word_len;

	n_toks = 0;
	while (*str)
	{
		str += space_len(str);
		tok_type = get_token_type(str);
		if (tok_type == TOKENTYPE_WORD)
		{
			word_len = get_word_len(str);
			if (word_len == -1)
				return (-1);
			str += word_len;
		}
		else if (tok_type == TOKENTYPE_NULL)
			continue ;
		else
			str += op_len(str);
		n_toks++;
	}
	return (n_toks);
}

int	get_word_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len] && !is_space(str[len]) && !is_metachar(str[len]))
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len++];
			len += inquote_len(str + len, quote);
			if (str[len] != quote)
				return (-1);
			quote = 0;
			len++;
		}
		len += letter_len(str + len);
	}
	return (len);
}

int	get_token_type(char *str)
{
	if (*str == 0)
		return (TOKENTYPE_NULL);
	if (*str == '|')
		return (TOKENTYPE_PIPE);
	else if (*str == '<' && *(str + 1) == '<')
		return (TOKENTYPE_REDIR_IN_HERE);
	else if (*str == '>' && *(str + 1) == '>')
		return (TOKENTYPE_REDIR_OUT_APPEND);
	else if (*str == '<')
		return (TOKENTYPE_REDIR_IN);
	else if (*str == '>')
		return (TOKENTYPE_REDIR_OUT);
	else
		return (TOKENTYPE_WORD);
}
